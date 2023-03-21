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
#define URL_TEMPLATE "https://romhustler.org/roms/%system%/%page%?sort_by=downloads&sort_order=desc&sort_region=all&filter=%query%"
#define URL_PREFIX "https://romhustler.org"
#define URL_FAVICON "https://romhustler.org/favicon.ico"

static acll_t *search(rl_system *system, char *searchString);

static void download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData);

static acll_t *fetchingResultItems(rl_system *system, acll_t *resultList, char *response);

static acll_t *fetchingResultDetails(rl_system *system, acll_t *resultList, char *response);

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

        chttp_response *faviconResponse = chttp_fetch(URL_FAVICON, NULL, NULL, GET, 0L);
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

        chttp_response *response = chttp_fetch(url, NULL, NULL, GET, 0L);
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
    chttp_response *detailPageResponse = chttp_fetch(item->url, NULL, NULL, GET, 1L);
    char *response = strstr(detailPageResponse->data, "<!doctype html>");

    char *regexString = "set-cookie: romhustler_session=([^;]+);";
    regexMatches_t *matches = regex_getMatches(detailPageResponse->data, regexString, 1);
    if (matches == NULL) {
        LOG_ERROR("Romhustler, cookie not found");
        return;
    }
    char *cookie = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);

    csafestring_t *cookieHeader = safe_create("cookie: ");
    safe_strcat(cookieHeader, cookie);
//    struct curl_slist *headers = curl_slist_append(NULL, cookieHeader->data);
    safe_destroy(cookieHeader);

    lxb_html_document_t *document = NULL;
    lxb_dom_collection_t *detailsCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                          "details-container");

    if (lxb_dom_collection_length(detailsCollection) != 1) {
        LOG_ERROR("Romhustler, table count of details-table not as expected");
        lxb_dom_collection_destroy(detailsCollection, true);
        lxb_html_document_destroy(document);
        chttp_free(detailPageResponse);
        return;
    }

    lxb_dom_collection_t *downloadLinksCollection = domparsing_createCollection(document);
    lxb_dom_element_t *detailsElement = lxb_dom_collection_element(detailsCollection, 0);

    domparsing_findChildElementsByTagName(downloadLinksCollection, detailsElement, "A", 1);

    if (lxb_dom_collection_length(downloadLinksCollection) != 1) {
        LOG_ERROR("Romhustler, download link not as expected");
        lxb_dom_collection_destroy(detailsCollection, true);
        lxb_dom_collection_destroy(downloadLinksCollection, true);
        lxb_html_document_destroy(document);
        chttp_free(detailPageResponse);
        return;
    }

    lxb_dom_element_t *linkElement = lxb_dom_collection_element(downloadLinksCollection, 0);
    char *downloadLink = domparsing_getAttributeValue(linkElement, "href");
    chttp_response *head = chttp_head(downloadLink, NULL);

    regexString = "Content-Disposition: attachment; filename=\"([^\"]+)\"";
    matches = regex_getMatches(head->data, regexString, 1);
    if (matches == NULL) {
        LOG_ERROR("Romhustler, filename not found");
        return;
    }
    char *filename = regex_cpyGroupText(matches, 0);
    regex_destroyMatches(matches);

    downloadCallbackFunction(appData, item->system, item->title, downloadLink, NULL, NULL, filename, GET);

    chttp_free(head);
    lxb_dom_collection_destroy(detailsCollection, true);
    lxb_dom_collection_destroy(downloadLinksCollection, true);
    lxb_html_document_destroy(document);
    chttp_free(detailPageResponse);
}

static acll_t *fetchingResultItems(rl_system *system, acll_t *resultList, char *response) {
    lxb_html_document_t *document = NULL;
    lxb_dom_collection_t *tablesCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                         "roms-table");
    lxb_dom_collection_t *tableLinkCollection = domparsing_createCollection(document);

    if (lxb_dom_collection_length(tablesCollection) < 1) {
        lxb_dom_collection_destroy(tablesCollection, true);
        lxb_dom_collection_destroy(tableLinkCollection, true);
        lxb_html_document_destroy(document);
        return resultList;
    }

    if (lxb_dom_collection_length(tablesCollection) != 1) {
        LOG_ERROR("Romhustler, table count of roms-tables not as expected");
        lxb_dom_collection_destroy(tablesCollection, true);
        lxb_dom_collection_destroy(tableLinkCollection, true);
        lxb_html_document_destroy(document);
        return resultList;
    }

    lxb_dom_element_t *tableElement = lxb_dom_collection_element(tablesCollection, 0);
    domparsing_findChildElementsByTagName(tableLinkCollection, tableElement, "A", 1);

    for (size_t i = 0; i < lxb_dom_collection_length(tableLinkCollection); i++) {
        lxb_dom_element_t *element = lxb_dom_collection_element(tableLinkCollection, i);
        char *url = str_concat(URL_PREFIX, domparsing_getAttributeValue(element, "href"));
        chttp_response *detailPageResponse = chttp_fetch(url, NULL, NULL, GET, 0L);
        resultList = fetchingResultDetails(system, resultList, detailPageResponse->data);
        chttp_free(detailPageResponse);
        free(url);
    }

    lxb_dom_collection_destroy(tablesCollection, true);
    lxb_dom_collection_destroy(tableLinkCollection, true);
    lxb_html_document_destroy(document);

    return resultList;
}

static acll_t *fetchingResultDetails(rl_system *system, acll_t *resultList, char *response) {
    lxb_html_document_t *document = NULL;
    lxb_dom_collection_t *tablesCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                         "details-table");
    lxb_dom_collection_t *downloadBtnCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                              "btn-yellow");
    lxb_dom_collection_t *tableLinkCollection = domparsing_createCollection(document);

    if (lxb_dom_collection_length(tablesCollection) != 1) {
        LOG_ERROR("Romhustler, table count of details-tables not as expected");
        return resultList;
    }

    if (lxb_dom_collection_length(downloadBtnCollection) != 1) {
        LOG_ERROR("Romhustler, table count of yellow-btn not as expected");
        return resultList;
    }

    rl_result *item = rl_result_create(system, hoster, NULL, NULL);

    lxb_dom_element_t *downloadBtn = lxb_dom_collection_element(downloadBtnCollection, 0);
    char *url = str_concat(URL_PREFIX, domparsing_getAttributeValue(downloadBtn, "href"));
    rl_result_setUrl(item, url);
    free(url);

    lxb_dom_element_t *tableElement = lxb_dom_collection_element(tablesCollection, 0);
    domparsing_findChildElementsByTagName(tableLinkCollection, tableElement, "TD", 1);

    for (size_t i = 0; i < lxb_dom_collection_length(tableLinkCollection); i++) {
        lxb_dom_element_t *element = lxb_dom_collection_element(tableLinkCollection, i);

        char *text = domparsing_getText(element);
        if (!strcmp(text, "Full Name")) {
            i++;
            element = lxb_dom_collection_element(tableLinkCollection, i);
            rl_result_setTitle(item, domparsing_getText(element));
        }
        if (!strcmp(text, "Filesize")) {
            i++;
            element = lxb_dom_collection_element(tableLinkCollection, i);
            rl_result_setFileSize(item, domparsing_getText(element));
        }
        if (!strcmp(text, "Can Download")) {
            i++;
            element = lxb_dom_collection_element(tableLinkCollection, i);
            if (strcmp(domparsing_getText(element), "Yes")) {
                rl_result_free(item);
                return resultList;
            }
        }
        if (!strcmp(text, "Rating")) {
            i++;
            element = lxb_dom_collection_element(tableLinkCollection, i);
            element = domparser_findFirstChildElementByAttribute(element, "class", "rateit", 0, 1);

            rl_result_setRating(item, domparsing_getAttributeValue(element, "data-rateit-value"), 5);
        }
    }
    resultList = acll_push(resultList, item);

    lxb_dom_collection_destroy(downloadBtnCollection, true);
    lxb_dom_collection_destroy(tablesCollection, true);
    lxb_dom_collection_destroy(tableLinkCollection, true);
    lxb_html_document_destroy(document);
    return resultList;
}

static uint32_t recalcPageCount(char *response) {
    lxb_html_document_t *document = NULL;
    lxb_dom_collection_t *paginationCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                             "page-item");

    if (lxb_dom_collection_length(paginationCollection) < 1) {
        lxb_dom_collection_destroy(paginationCollection, true);
        lxb_html_document_destroy(document);
        return 0;
    }

    lxb_dom_element_t *paginationElement = lxb_dom_collection_element(paginationCollection,
                                                                      lxb_dom_collection_length(paginationCollection) -
                                                                      2);
    char *pages = domparsing_getText(paginationElement);
    return atoi(pages);
}
