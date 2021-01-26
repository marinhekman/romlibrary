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
#include "romlibrary.h"
#include "src/helper/utils.h"

static void freeFields(void *ptr);

static int result_sortComparator(void *payload1, void *payload2);

rl_result *rl_result_create(rl_system *system, rl_hoster *hoster, char *title, char *url) {
    rl_result *result = (rl_result *) calloc(1, sizeof(rl_result));
    result->title = NULL;
    result->url = NULL;
    result->hoster = hoster;
    result->system = system;
    result->downloads = 0;
    result->rating = 0;
    result->fileSize = NULL;

    rl_result_setTitle(result, title);
    rl_result_setUrl(result, url);
    return result;
}

void rl_result_setTitle(rl_result *result, char *title) {
    title = str_trim(title);
    LOG_DEBUG("Title: %s", title);
    if (result == NULL || title == NULL) {
        return;
    }
    result->title = str_clone(title);
}

void rl_result_setUrl(rl_result *result, char *url) {
    url = str_trim(url);
    LOG_DEBUG("URL: %s", url);
    if (result == NULL || url == NULL) {
        return;
    }
    result->url = str_clone(url);
}

void rl_result_setDownloads(rl_result *result, char *downloads) {
    downloads = str_trim(downloads);
    LOG_DEBUG("DOWNLOADS: %s", downloads);
    if (downloads == NULL) {
        return;
    }
    result->downloads = atoi(downloads);
    LOG_DEBUG("Calc'd Downloads: %d", result->downloads);
}

void rl_result_setRating(rl_result *result, char *rating, uint8_t maxRating) {
    rating = str_trim(rating);
    LOG_DEBUG("RATING: %s", rating);
    if (rating == NULL) {
        return;
    }
    result->rating = (maxRating == 10) ? 1.0f * atof(rating) : 2.0f * atof(rating);
    LOG_DEBUG("Calc'd Rating: %2.1f", result->rating);
}

void rl_result_setFileSize(rl_result *result, char *fileSize) {
    fileSize = str_trim(fileSize);
    LOG_DEBUG("FILE SIZE: %s", fileSize);
    if (fileSize == NULL) {
        return;
    }
    result->fileSize = str_clone(fileSize);
}

void rl_results_free(acll_t *results) {
    acll_free(results, &freeFields);
}

acll_t *rl_results_sort(acll_t *results) {
    return acll_sort(results, result_sortComparator);
}


static int result_sortComparator(void *payload1, void *payload2) {
    rl_result *result1 = payload1;
    rl_result *result2 = payload2;
    return strcmp(result1->title, result2->title);
}

static void freeFields(void *ptr) {
    rl_result *resultList = (rl_result *) ptr;
    FREENOTNULL(resultList->title);
    FREENOTNULL(resultList->url);
    FREENOTNULL(resultList->fileSize);
}