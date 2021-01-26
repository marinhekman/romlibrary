/*
 * Copyright 2020 - 2021 Maximilian Voss (maximilian@voss.rocks)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <csafestring.h>
#include "../../helper/domparsing.h"
#include "romhustler.h"
#include "../urlhandling.h"
#include "mapping.h"
#include "src/helper/utils.h"
#include "../../helper/regex.h"

#define SHORTNAME "HSL"
#define FULLNAME "https://romhustler.org"
#define URL_TEMPLATE "https://romhustler.org/roms/search/page:%page%?q=%query%&console_id%5B9%5D=%system%"
#define URL_PREFIX "https://romhustler.org"
#define URL_DOWNLOAD_LINK "https://romhustler.org/link/"
#define URL_FAVICON "https://romhustler.org/favicon.ico"

static acll_t *search(rl_system *system, char *searchString);

static void download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData);

static acll_t *fetchingResultItems(rl_system *system, acll_t *resultList, char *response);

static char *fetchId(char *response);

static char *fetchDownloadLink(char *response);

static uint32_t recalcPageCount(char *response);

static rl_hoster *hoster = NULL;

rl_hoster *romhustler_getHoster(rl_cache *cacheHandler) {
    if (hoster == NULL) {
        hoster = calloc(1, sizeof(rl_hoster));
        hoster->name = SHORTNAME;
        hoster->fullname = FULLNAME;
        hoster->active = 1;
        hoster->search = search;
        hoster->download = download;
        hoster->cacheHandler = cacheHandler;

        chttp_response *faviconResponse = chttp_fetch(URL_FAVICON, NULL, GET, 0L);
        hoster->favicon = calloc(1, sizeof(rl_image));
        hoster->favicon->binary = calloc(faviconResponse->size, sizeof(char));
        memcpy(hoster->favicon->binary, faviconResponse->data, sizeof(char) * faviconResponse->size);
        hoster->favicon->size = faviconResponse->size;
        chttp_free(faviconResponse);
    }
    return hoster;
}

static acll_t *search(rl_system *system, char *searchString) {
    uint32_t page = 1;
    uint32_t pageCount = 1;
    char *urlTemplate = URL_TEMPLATE;

    acll_t *resultList = NULL;

    while (page <= pageCount) {
        char *url = urlhandling_substitudeVariables(urlTemplate, system, &romhustler_deviceMapping, searchString, page);
        if (url == NULL) {
            break;
        }

        chttp_response *response = chttp_fetch(url, NULL, GET, 0L);
        resultList = fetchingResultItems(system, resultList, response->data);

        if (pageCount == 1) {
            pageCount = recalcPageCount(response->data);
        }

        chttp_free(response);
        free(url);

        page++;
    }
    return resultList;
}

static void download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData) {
    if (item == NULL) {
        return;
    }
    chttp_response *detailPageResponse = chttp_fetch(item->url, NULL, GET, 1L);
    char *id = fetchId(detailPageResponse->data);

    csafestring_t *linkUrl = safe_create(URL_DOWNLOAD_LINK);
    safe_strcat(linkUrl, id);
    chttp_response *linkJsonResponse = chttp_fetch(linkUrl->data, NULL, GET, 1L);

    char *downloadLink = fetchDownloadLink(linkJsonResponse->data);
    char *decodedDownloadLink = str_quoteDecode(downloadLink);

    char *filename = str_concat(item->title, file_suffix(decodedDownloadLink));
    downloadCallbackFunction(appData, item->system, item->title, decodedDownloadLink, NULL, filename, GET);

    free(filename);
    chttp_free(linkJsonResponse);
    free(id);
    free(downloadLink);
    free(decodedDownloadLink);
    chttp_free(detailPageResponse);
    safe_destroy(linkUrl);
}

static acll_t *fetchingResultItems(rl_system *system, acll_t *resultList, char *response) {
    lxb_html_document_t *document;
    lxb_dom_collection_t *gamesCollection = domparsing_getElementsCollectionByClassName(response, &document, "row");
    lxb_dom_collection_t *gameElementCollection = domparsing_createCollection(document);

    for (size_t i = 1; i < lxb_dom_collection_length(gamesCollection); i++) {
        lxb_dom_element_t *gameParent = lxb_dom_collection_element(gamesCollection, i);
        rl_result *item = rl_result_create(system, hoster, NULL, NULL);

        domparsing_findChildElementsByTagName(gameElementCollection, gameParent, "DIV", 1);

        lxb_dom_element_t *element;
        element = lxb_dom_collection_element(gameElementCollection, 0);
        rl_result_setTitle(item, domparsing_getText(element));

        element = domparser_findFirstChildElementByTagName(element, "A", 1);
        char *url = str_concat(URL_PREFIX, domparsing_getAttributeValue(element, "href"));
        rl_result_setUrl(item, url);
        free(url);

        element = lxb_dom_collection_element(gameElementCollection, 2);
        char *downloads = domparsing_getText(element);
        rl_result_setDownloads(item, downloads);

        element = lxb_dom_collection_element(gameElementCollection, 3);
        char *rating = domparsing_getText(element);
        rl_result_setRating(item, rating, 5);

        lxb_dom_collection_clean(gameElementCollection);
        resultList = acll_push(resultList, item);
    }
    lxb_dom_collection_destroy(gameElementCollection, true);
    lxb_dom_collection_destroy(gamesCollection, true);
    lxb_html_document_destroy(document);

    return resultList;
}

static char *fetchId(char *response) {
    char *regexString = "var download_id = ([^;]+);";

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *id = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    return id;
}

static char *fetchDownloadLink(char *response) {
    char *regexString = "\"direct\":\"([^\"]+)\"";

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *link = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    return link;
}

static uint32_t recalcPageCount(char *response) {
    lxb_html_document_t *document;
    lxb_dom_collection_t *navContainer = domparsing_getElementsCollectionByClassName(response, &document, "pagi_nav");
    lxb_dom_collection_t *navItems = domparsing_createCollection(document);

    if (!lxb_dom_collection_length(navContainer)) {
        return 0;
    }

    lxb_dom_element_t *navContainerElement = lxb_dom_collection_element(navContainer, 0);
    domparsing_findChildElementsByTagName(navItems, navContainerElement, "SPAN", 1);

    lxb_dom_element_t *navItemElement = lxb_dom_collection_element(navItems, lxb_dom_collection_length(navItems) - 1);
    char *pagesString = domparsing_getText(navItemElement);

    regexMatches_t *matches = regex_getMatches(pagesString, "Page [0-9]+ of ([0-9]+)", 1);
    if (matches == NULL) {
        return 1;
    }
    char *pages = regex_cpyGroupText(matches, 0);
    int retVal = atoi(pages);
    regex_destroyMatches(matches);

    lxb_dom_collection_destroy(navContainer, true);
    lxb_dom_collection_destroy(navItems, true);
    lxb_html_document_destroy(document);

    return retVal;
}
