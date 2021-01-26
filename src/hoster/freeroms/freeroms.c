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

#include <pthread.h>
#include <csafestring.h>
#include "../../helper/domparsing.h"
#include "freeroms.h"
#include "mapping.h"
#include "../../common/utils.h"
#include "../urlhandling.h"

#define SHORTNAME "FRE"
#define FULLNAME "https://freeroms.com"
#define URL_TEMPLATE_NUM "https://www.freeroms.com/%system%_roms_NUM.htm"
#define URL_TEMPLATE_CHAR "https://www.freeroms.com/%system%_roms_%query%.htm"
#define URL_TEMPLATE_DOWNLOAD "https://www.freeroms.com/dl_roms/rom_download_tr.php?system=%system%&game_id=%id%"
#define URL_FAVICON "https://www.freeroms.com/favicon.ico"

static acll_t *search(rl_system *system, char *searchString);

static void download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData);

static void fillCache(rl_system *system);

static void *executeThread(void *ptr);

static void extractLink(rl_system *system, char *response);

static char *generateDownloadLink(rl_system *system, char *id);

struct s_download_filter {
    char start;
    char end;
    rl_system *system;
};

static rl_hoster *hoster = NULL;

rl_hoster *freeroms_getHoster(rl_cache *cacheHandler) {
    if (cacheHandler == NULL) {
        return NULL;
    }
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
        memcpy(hoster->favicon->binary, faviconResponse->data, faviconResponse->size);
        hoster->favicon->size = faviconResponse->size;
        chttp_free(faviconResponse);
    }
    return hoster;
}

static acll_t *search(rl_system *system, char *searchString) {
    if (!hoster->cacheHandler->isValid(hoster, system, hoster->cacheHandler->data)) {
        LOG_DEBUG("Cache is invalid and needs to be rebuilt");
        hoster->cacheHandler->clear(hoster, system, hoster->cacheHandler->data);
        fillCache(system);
        hoster->cacheHandler->touch(hoster, system, hoster->cacheHandler->data);
        LOG_DEBUG("Rebuilding complete");
    }
    LOG_DEBUG("Retrieve search result from Cache");
    return hoster->cacheHandler->get(hoster, system, searchString, hoster->cacheHandler->data);
}

static void download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData) {
    if (item == NULL) {
        return;
    }

    char *filename = str_concat(item->title, ".zip");
    downloadCallbackFunction(appData, item->system, item->title, item->url, NULL, filename, GET);
    FREENOTNULL(filename);
}

static void fillCache(rl_system *system) {
    pthread_t thread[RL_THREAD_COUNT];
    struct s_download_filter filter[RL_THREAD_COUNT];

    char chunks = ('Z' - '@') / RL_THREAD_COUNT;
    for (int i = 0; i < RL_THREAD_COUNT; i++) {
        filter[i].start = (char) '@' + i * chunks;
        filter[i].end = (char) '@' + (i + 1) * chunks - 1;
        filter[i].system = system;
    }
    filter[RL_THREAD_COUNT - 1].end = 'Z';

    for (int i = 0; i < RL_THREAD_COUNT; i++) {
        pthread_create(&thread[i], NULL, executeThread, &filter[i]);
    }
    for (int i = RL_THREAD_COUNT - 1; i >= 0; i--) {
        pthread_join(thread[i], NULL);
    }
}


static void *executeThread(void *ptr) {
    struct s_download_filter *filter = (struct s_download_filter *) ptr;

    for (char chr = filter->start; chr <= filter->end; chr++) {
        char *url;
        chttp_response *response;
        if (chr == '@') {
            url = urlhandling_substitudeVariables(URL_TEMPLATE_NUM, filter->system, &freeroms_deviceMapping, "", 0);
            if (url == NULL) {
                break;
            }
            response = chttp_fetch(url, NULL, GET, 1L);
            extractLink(filter->system, response->data);
        } else {
            char str[2] = {0, 0};
            str[0] = chr;
            url = urlhandling_substitudeVariables(URL_TEMPLATE_CHAR, filter->system, &freeroms_deviceMapping, str,
                                                  0);
            if (url == NULL) {
                break;
            }
            response = chttp_fetch(url, NULL, GET, 1L);
            extractLink(filter->system, response->data);
        }
        chttp_free(response);
        FREENOTNULL(url);
    }

    return NULL;
}

static void extractLink(rl_system *system, char *response) {
    acll_t *results = NULL;
    lxb_html_document_t *document;
    lxb_dom_collection_t *gamesCollection = domparsing_getElementsCollectionByClassName(response, &document,
                                                                                        "system-rom-tr-wrap");
    lxb_dom_collection_t *gameElementCollection = domparsing_createCollection(document);

    for (size_t i = 0; i < lxb_dom_collection_length(gamesCollection); i++) {
        lxb_dom_element_t *gameParent = lxb_dom_collection_element(gamesCollection, i);
        rl_result *item = rl_result_create(system, hoster, NULL, NULL);

        domparsing_findChildElementsByTagName(gameElementCollection, gameParent, "DIV", 1);

        lxb_dom_element_t *element;
        element = lxb_dom_collection_element(gameElementCollection, 0);
        rl_result_setTitle(item, domparsing_getText(element));

        element = lxb_dom_collection_element(gameElementCollection, 1);
        element = domparser_findFirstChildElementByTagName(element, "A", 1);
        char *gameId = (char *) domparsing_getAttributeValue(element, "onclick");
        gameId = str_replace(gameId, "window.open('/vote.php?game_id=", "");
        gameId = str_replace(gameId, "', 'votewindow', 'width=450, height=400'); return false;", "");
        rl_result_setUrl(item, generateDownloadLink(system, gameId));

        element = lxb_dom_collection_element(gameElementCollection, 3);
        char *rating = domparsing_getText(element);
        rating = str_replace(rating, "/10", "");
        rl_result_setRating(item, rating, 10);

        results = acll_push(results, item);
        lxb_dom_collection_clean(gameElementCollection);
    }
    lxb_dom_collection_destroy(gameElementCollection, true);
    lxb_dom_collection_destroy(gamesCollection, true);
    lxb_html_document_destroy(document);

    acll_t *ptr = acll_first(results);
    while (ptr != NULL) {
        hoster->cacheHandler->add(hoster, system, NULL, rl_getResult(ptr), hoster->cacheHandler->data);
        ptr = ptr->next;
    }
    rl_results_destroy(results);
}


static char *generateDownloadLink(rl_system *system, char *id) {
    char *systemStr = freeroms_deviceMapping(system);
    if (systemStr == NULL) {
        LOG_INFO("Found no mapping for system: %s", system->fullname);
        return NULL;
    }

    char *result;
    char *tmp;

    result = str_replace(URL_TEMPLATE_DOWNLOAD, "%id%", id);

    tmp = result;
    result = str_replace(tmp, "%system%", systemStr);
    FREENOTNULL(tmp);

    return result;
}
