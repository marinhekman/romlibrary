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

#include <string.h>
#include "../../romlibrary.h"
#include "../common/utils.h"

static void freeFields(void *ptr);

static int result_sortComparator(void *payload1, void *payload2);

result_t *result_create(system_t *system, hoster_t *hoster, char *title, char *url) {
    result_t *result = (result_t *) calloc(1, sizeof(result_t));
    result->title = NULL;
    result->url = NULL;
    result->hoster = hoster;
    result->system = system;
    result->downloads = 0;
    result->rating = 0;
    result->fileSize = NULL;

    result_setTitle(result, title);
    result_setUrl(result, url);
    return result;
}

void result_setTitle(result_t *result, char *title) {
    title = str_trim(title);
    LOG_DEBUG("Title: %s", title);
    if (result == NULL || title == NULL) {
        return;
    }
    result->title = str_clone(title);
}

void result_setUrl(result_t *result, char *url) {
    url = str_trim(url);
    LOG_DEBUG("URL: %s", url);
    if (result == NULL || url == NULL) {
        return;
    }
    result->url = str_clone(url);
}

void result_setDownloads(result_t *result, char *downloads) {
    downloads = str_trim(downloads);
    LOG_DEBUG("DOWNLOADS: %s", downloads);
    if (downloads == NULL) {
        return;
    }
    result->downloads = atoi(downloads);
    LOG_DEBUG("Calc'd Downloads: %d", result->downloads);
}

void result_setRating(result_t *result, char *rating, uint8_t maxRating) {
    rating = str_trim(rating);
    LOG_DEBUG("RATING: %s", rating);
    if (rating == NULL) {
        return;
    }
    result->rating = (maxRating == 10) ? 1.0f * atof(rating) : 2.0f * atof(rating);
    LOG_DEBUG("Calc'd Rating: %2.1f", result->rating);
}

void result_setFileSize(result_t *result, char *fileSize) {
    fileSize = str_trim(fileSize);
    LOG_DEBUG("FILE SIZE: %s", fileSize);
    if (fileSize == NULL) {
        return;
    }
    result->fileSize = str_clone(fileSize);
}

void result_freeList(acll_t *results) {
    acll_free(results, &freeFields);
}

acll_t *result_sort(acll_t *results) {
    return acll_sort(results, result_sortComparator);
}


static int result_sortComparator(void *payload1, void *payload2) {
    result_t *result1 = payload1;
    result_t *result2 = payload2;
    return strcmp(result1->title, result2->title);
}

static void freeFields(void *ptr) {
    result_t *resultList = (result_t *) ptr;
    FREENOTNULL(resultList->title);
    FREENOTNULL(resultList->url);
    FREENOTNULL(resultList->fileSize);
}