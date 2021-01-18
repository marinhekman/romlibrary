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

#include <romlibrary.h>
#include <pthread.h>
#include <string.h>
#include "romhustler/romhustler.h"
#include "romsdownload/romsdownload.h"
#include "romsemulator/romsemulator.h"
#include "romsmania/romsmania.h"
#include "wowroms/wowroms.h"
#include "freeroms/freeroms.h"

static void *executeThread(void *searchPtr);

typedef struct {
    hoster_t *hoster;
    system_t *system;
    char *searchString;
    pthread_t thread;
    acll_t *result;
} search_t;

acll_t *hosterhandler_init(cache_t *cacheHandler) {
    acll_t *hosters = NULL;
    hosters = acll_append(hosters, freeroms_getHoster(cacheHandler));
    hosters = acll_append(hosters, romhustler_getHoster(cacheHandler));
    hosters = acll_append(hosters, romsdownload_getHoster(cacheHandler));
    hosters = acll_append(hosters, romsemulator_getHoster(cacheHandler));
    hosters = acll_append(hosters, romsmania_getHoster(cacheHandler));
    hosters = acll_append(hosters, wowroms_getHoster(cacheHandler));
    return hosters;
}

acll_t *hosterhandler_search(acll_t *hosters, system_t *system, char *searchString) {
    acll_t *result = NULL;
    acll_t *ptr = hosters;

    uint32_t count = acll_count(ptr);
    search_t *searches = (search_t *) calloc(count, sizeof(search_t));

    int activeNumber = 0;
    while (ptr != NULL) {
        if (getHoster(ptr)->active) {
            searches[activeNumber].hoster = getHoster(ptr);
            searches[activeNumber].system = system;
            searches[activeNumber].searchString = searchString;
            searches[activeNumber].result = NULL;
            pthread_create(&searches[activeNumber].thread, NULL, executeThread, &searches[activeNumber]);
            activeNumber++;
        }
        ptr = ptr->next;
    }

    for (int i = 0; i < activeNumber; i++) {
        pthread_join(searches[i].thread, NULL);
        result = acll_concat(result, searches[i].result);
    }

    return result_sort(result);
}

void hosterhandler_download(result_t *item, downloadCallback_t downloadCallbackFunction, void *appData) {
    item->hoster->download(item, downloadCallbackFunction, appData);
}

void hosterhandler_destroy(acll_t *hoster) {
    acll_free(hoster, NULL);
}

int hoster_findByFullname(void *payload, void *input) {
    hoster_t *hoster = payload;
    char *fullname = input;

    return !strcmp(hoster->fullname, fullname);
}

int hoster_findByName(void *payload, void *input) {
    hoster_t *hoster = payload;
    char *name = input;

    return !strcmp(hoster->name, name);
}

static void *executeThread(void *searchPtr) {
    search_t *search = (search_t *) searchPtr;
    LOG_DEBUG("Call search on: %s", search->hoster->name);
    search->result = search->hoster->search(search->system, search->searchString);
    LOG_DEBUG("Done with search on: %s", search->hoster->name);
    return NULL;
}
