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
#include <time.h>
#include "../../helper/domparsing.h"
#include "wowroms.h"
#include "mapping.h"
#include "../urlhandling.h"
#include "../../common/utils.h"
#include "../../helper/regex.h"
#include "../../helper/md5.h"

#define SHORTNAME "WOW"
#define FULLNAME "https://www.wowroms.com"
#define URL_TEMPLATE "https://wowroms.com/en/roms/list/%system%?search=%query%&page=%page%"
#define URL_PREFIX "https://wowroms.com"
#define URL_FAVICON "https://www.wowroms.com/assets/images/favicon.jpg"

static acll_t *search(system_t *system, char *searchString);

static void download(result_t *item, downloadCallback_t downloadCallbackFunction, void *appData);

static acll_t *fetchingResultItems(system_t *system, acll_t *resultList, char *response);

static char *fetchDownloadPageLink(char *response);

static char *fetchDownloadServlet(char *response);

static char *fetchHiddenField(char *text, char *fieldname);

static char *fetchDownloadLink(char *response);

static uint32_t recalcPageCount(char *response);

static hoster_t *hoster = NULL;

hoster_t *wowroms_getHoster(cache_t *cacheHandler) {
    if (hoster == NULL) {
        hoster = calloc(1, sizeof(hoster_t));
        hoster->name = SHORTNAME;
        hoster->fullname = FULLNAME;
        hoster->active = 1;
        hoster->search = search;
        hoster->download = download;
        hoster->cacheHandler = cacheHandler;

        chttp_response *faviconResponse = chttp_fetch(URL_FAVICON, NULL, GET, 0L);
        hoster->favicon = calloc(1, sizeof(memimage_t));
        hoster->favicon->binary = calloc(faviconResponse->size, sizeof(char));
        memcpy(hoster->favicon->binary, faviconResponse->data, faviconResponse->size);
        hoster->favicon->size = faviconResponse->size;
        chttp_free(faviconResponse);
    }
    return hoster;
}


static acll_t *search(system_t *system, char *searchString) {
    uint32_t pageCount = 1;
    uint32_t page = 1;
    char *urlTemplate = URL_TEMPLATE;

    acll_t *resultList = NULL;
    while (page <= pageCount) {
        char *url = urlhandling_substitudeVariables(urlTemplate, system, &wowroms_deviceMapping, searchString, page);
        if (url == NULL) {
            break;
        }

        chttp_response *response = chttp_fetch(url, NULL, GET, 1L);
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

static void download(result_t *item, downloadCallback_t downloadCallbackFunction, void *appData) {
    if (item == NULL) {
        return;
    }

    char timestamp[20];
    sprintf(timestamp, "%u", (unsigned) time(NULL));
    char *timestampMD5 = md5_str2md5(timestamp);
    char timeToken[255];
    snprintf(timeToken, 255, "?k=%s&t=%s", timestamp, timestampMD5);

    chttp_response *detailPageResponse = chttp_fetch(item->url, NULL, GET, 1L);
    char *linkDownloadPageRelative = fetchDownloadPageLink(detailPageResponse->data);
    char *linkDownloadPage = str_concat(URL_PREFIX, linkDownloadPageRelative);

    chttp_response *downloadPageResponse = chttp_fetch(linkDownloadPage, NULL, GET, 1L);
    char *downloadServletRel = fetchDownloadServlet(downloadPageResponse->data);
    char *downloadServlet = str_concat(URL_PREFIX, downloadServletRel);

    char *filename = fetchHiddenField(downloadPageResponse->data, "file");
    char *id = fetchHiddenField(downloadPageResponse->data, "id");
    char *emuid = fetchHiddenField(downloadPageResponse->data, "emuid");
    char *downloadServletUrl = str_concat(downloadServlet, timeToken);

    chttp_response *downloadServletResponse = chttp_fetch(downloadServletUrl, "", POST, 1L);
    char *downloadLink = fetchDownloadLink(downloadServletResponse->data);
    char *decodedDownloadLink = str_quoteDecode(downloadLink);

    csafestring_t *payload = safe_create("emuid=");
    safe_strcat(payload, emuid);
    safe_strcat(payload, "&id=");
    safe_strcat(payload, id);
    safe_strcat(payload, "&file=");
    safe_strcat(payload, filename);

    char *decodedFilename = str_urlDecode(filename);

    char *downloadFilename = str_concat(item->title, file_suffix(fetchHiddenField(downloadPageResponse->data, "file")));
    downloadCallbackFunction(appData, item->system, item->title, decodedDownloadLink, payload->data, downloadFilename,
                             POST);
    free(downloadFilename);

    free(decodedFilename);
    free(decodedDownloadLink);
    free(downloadServletUrl);
    chttp_free(downloadServletResponse);
    free(filename);
    free(emuid);
    free(id);
    free(timestampMD5);
    free(downloadServletRel);
    chttp_free(detailPageResponse);
    free(linkDownloadPageRelative);
    free(linkDownloadPage);
    chttp_free(downloadPageResponse);
    free(downloadServlet);
    free(downloadLink);
    safe_destroy(payload);
}

static char *fetchHiddenField(char *response, char *fieldname) {
    char *regexStringTmpl = "<input type=\"hidden\" name=\"%fieldname%\" value=\"([^\"]+)\" />";
    char *regexString = str_replace(regexStringTmpl, "%fieldname%", fieldname);

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *link = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    free(regexString);
    return link;
}

static char *fetchDownloadServlet(char *response) {
    char *regexString = "var ajaxLinkUrl = \"([^\"]+)\";";

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *link = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    return link;
}

static char *fetchDownloadLink(char *response) {
    char *regexString = "\"link\":\"([^\"]+)\"";

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *link = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    return link;
}

static char *fetchDownloadPageLink(char *response) {
    char *regexString = "<a class=\"[^\"]+\" style=\"[^\"]+\" href=\"([^\"]+)\">Download [^<]+</a>";

    regexMatches_t *matches = regex_getMatches(response, regexString, 1);
    if (matches == NULL) {
        return NULL;
    }
    char *link = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);
    return link;
}

static acll_t *fetchingResultItems(system_t *system, acll_t *resultList, char *response) {
    lxb_html_document_t *document;
    lxb_dom_collection_t *gamesCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                        "group_info");
    lxb_dom_collection_t *gameElementCollection = domparsing_createCollection(document);

    for (size_t i = 0; i < lxb_dom_collection_length(gamesCollection); i++) {
        lxb_dom_element_t *gameParent = lxb_dom_collection_element(gamesCollection, i);
        result_t *item = result_create(system, hoster, NULL, NULL);

        domparsing_findChildElementsByTagName(gameElementCollection, gameParent, "A", 1);

        lxb_dom_element_t *element;
        element = lxb_dom_collection_element(gameElementCollection, 0);
        result_setTitle(item, domparsing_getText(element));

        char *url = str_concat(URL_PREFIX, domparsing_getAttributeValue(element, "href"));
        result_setUrl(item, url);
        free(url);

        element = lxb_dom_collection_element(gameElementCollection, 3);
        char *fileSize = domparsing_getText(element);
        fileSize = str_replace(fileSize, "File Size : ", "");
        result_setFileSize(item, fileSize);

        element = lxb_dom_collection_element(gameElementCollection, 4);
        char *downloads = domparsing_getText(element);
        downloads = str_replace(downloads, "Downlaod : ", "");
        result_setDownloads(item, downloads);

        element = lxb_dom_collection_element(gameElementCollection, 5);
        char *rating = domparsing_getText(element);
        rating = str_replace(rating, "Rating : ", "");
        result_setRating(item, rating, 5);

        lxb_dom_collection_clean(gameElementCollection);
        resultList = acll_push(resultList, item);
    }
    lxb_dom_collection_destroy(gameElementCollection, true);
    lxb_dom_collection_destroy(gamesCollection, true);
    lxb_html_document_destroy(document);

    return resultList;
}


static uint32_t recalcPageCount(char *response) {
    lxb_html_document_t *document;
    lxb_dom_collection_t *navContainer = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                     "top-paginate");
    lxb_dom_collection_t *navItem = domparsing_createCollection(document);

    if (!lxb_dom_collection_length(navContainer)) {
        return 0;
    }

    lxb_dom_element_t *navContainerElement = lxb_dom_collection_element(navContainer, 0);
    domparsing_findChildElementsByTagName(navItem, navContainerElement, "LI", 1);

    lxb_dom_element_t *navItemElement = lxb_dom_collection_element(navItem,
                                                                   lxb_dom_collection_length(navItem) - 1);

    lxb_dom_element_t *anchorElement = domparser_findFirstChildElementByTagName(navItemElement, "A", 0);
    char *href = domparsing_getAttributeValue(anchorElement, "href");

    char *regexString = "page=([0-9]+)";
    regexMatches_t *matches = regex_getMatches(href, regexString, 1);
    if (matches == NULL) {
        lxb_dom_collection_destroy(navContainer, true);
        lxb_dom_collection_destroy(navItem, true);
        lxb_html_document_destroy(document);
        return 1;
    }
    char *pages = regex_cpyGroupText(matches, 0);
    int retVal = atoi(pages);

    regex_destroyMatches(matches);
    lxb_dom_collection_destroy(navContainer, true);
    lxb_dom_collection_destroy(navItem, true);
    lxb_html_document_destroy(document);
    free(pages);

    return retVal;
}