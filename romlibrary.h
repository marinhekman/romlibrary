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

#ifndef _ROMLIBRARY_H
#define _ROMLIBRARY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <acll.h>
#include <chttp.h>
#include <clogger.h>

// define the number of parallel threads to fetch content from hosters
#ifndef RL_THREAD_COUNT
#define RL_THREAD_COUNT 5
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Typedefs
typedef struct rl_result_s rl_result;
typedef struct rl_system_s rl_system;
typedef struct rl_image_s rl_image;
typedef struct rl_hoster_s rl_hoster;
typedef struct rl_cache_s rl_cache;

// Gaming System
struct rl_system_s {
    char *fullname;
    uint8_t active;
    char *name;
    char *path;
};

// Callback to run downloads
typedef uint8_t (*rl_download_callback_function)(void *appData, struct rl_system_s *system, char *title, char *url,
                                                 char *data,
                                                 char *filename,
                                                 chttp_method method);

// Memory Image or any other data object where data & size is needed
struct rl_image_s {
    size_t size;
    char *binary;
};

// Hoster of ROMs
struct rl_hoster_s {
    char *fullname;
    uint8_t active;
    char *name;
    struct rl_cache_s *cacheHandler;
    struct rl_image_s *favicon;

    acll_t *(*search)(rl_system *system, char *searchString);

    void (*download)(rl_result *item, rl_download_callback_function callbackFunction, void *data);
};

// Search Result
struct rl_result_s {
    char *title;
    char *url;
    float rating;
    int32_t downloads;
    char *fileSize;
    rl_system *system;
    rl_hoster *hoster;
};

// Caching of search results or hoster's content
struct rl_cache_s {
    void *data;

    uint8_t (*isValid)(struct rl_hoster_s *hoster, struct rl_system_s *system, void *data);

    void (*clear)(struct rl_hoster_s *hoster, struct rl_system_s *system, void *data);

    void
    (*add)(struct rl_hoster_s *hoster, struct rl_system_s *system, char *searchString, rl_result *entry, void *data);

    acll_t *(*get)(struct rl_hoster_s *hoster, struct rl_system_s *system, char *searchString, void *data);

    void (*touch)(struct rl_hoster_s *hoster, struct rl_system_s *system, void *data);
};

// Loads RL library
void rl_loadLibraryFunctions(void *libHandler);

#ifdef RL_DYNAMIC
// Exported dynamic methods
// systems
acll_t *(*rl_systems_init)();

void (*rl_system_free)(acll_t *systems);

int (*rl_system_findByFullname)(void *payload, void *input);

// hoster
acll_t *(*rl_hoster_init)(rl_cache *cacheHandler);

acll_t *(*rl_search)(acll_t *hosters, rl_system *system, char *searchString);

void (*rl_download)(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData);

void (*rl_hoster_free)(acll_t *hoster);

int (*rl_hoster_findByFullname)(void *payload, void *input);

int (*rl_hoster_findByName)(void *payload, void *input);

// results
rl_result *(*rl_result_create)(rl_system *system, rl_hoster *hoster, char *title, char *url);

void (*rl_result_setTitle)(rl_result *result, char *title);

void (*rl_result_setUrl)(rl_result *result, char *url);

void (*rl_result_setDownloads)(rl_result *result, char *downloads);

void (*rl_result_setRating)(rl_result *result, char *rating, uint8_t maxRating);

void (*rl_result_setFileSize)(rl_result *result, char *fileSize);

void (*rl_results_free)(acll_t *results);

acll_t *(*rl_results_sort)(acll_t *results);

#else

// Exported static methods
// systems
acll_t *rl_systems_init();

void rl_system_free(acll_t *systems);

int rl_system_findByFullname(void *payload, void *input);

// hoster
acll_t *rl_hoster_init(rl_cache *cacheHandler);

acll_t *rl_search(acll_t *hosters, rl_system *system, char *searchString);

void rl_download(rl_result *item, rl_download_callback_function downloadCallbackFunction, void *appData);

void rl_hoster_free(acll_t *hoster);

int rl_hoster_findByFullname(void *payload, void *input);

int rl_hoster_findByName(void *payload, void *input);

// results
rl_result *rl_result_create(rl_system *system, rl_hoster *hoster, char *title, char *url);

void rl_result_setTitle(rl_result *result, char *title);

void rl_result_setUrl(rl_result *result, char *url);

void rl_result_setDownloads(rl_result *result, char *downloads);

void rl_result_setRating(rl_result *result, char *rating, uint8_t maxRating);

void rl_result_setFileSize(rl_result *result, char *fileSize);

void rl_results_free(acll_t *results);

acll_t *rl_results_sort(acll_t *results);

#endif

// nice macros for method calling
// systems
#define rl_systems_findByFullname(systems, fullname) acll_find(systems, rl_system_findByFullname, fullname)
#define rl_getSystem(system) ((rl_system *) system->payload)

// hoster
#define rl_hosters_findByFullname(hosters, fullname) acll_find(hosters, rl_hoster_findByFullname, fullname)
#define rl_hosters_findByName(hosters, name) acll_find(hosters, hoster_findByName, name)
#define rl_getHoster(hoster) ((rl_hoster *) hoster->payload)

// results
#define rl_getResult(result) ((rl_result *) result->payload)

#ifdef __cplusplus
}
#endif

#endif
