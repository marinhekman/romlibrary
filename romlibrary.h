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

#ifndef ROMFETCHER_H
#define ROMFETCHER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <curl/curl.h>
#include <acll.h>

// Typedefs
// HTTP Method Enum
typedef enum {
    GET,
    POST
} httpmethod_t;

typedef struct result_s result_t;
typedef struct system_s system_t;
typedef struct memimage_s memimage_t;
typedef struct hoster_s hoster_t;
typedef struct cache_s cache_t;
typedef struct http_response_s http_response_t;

// Gaming System
struct system_s {
    char *fullname;
    uint8_t active;
    char *name;
    char *path;
};

// Callback to run downloads
typedef uint8_t (*downloadCallback_t)(void *appData, struct system_s *system, char *title, char *url, char *data,
                                      char *filename,
                                      httpmethod_t method);

// Memory Image or any other data object where data & size is needed
struct memimage_s {
    size_t size;
    char *binary;
};

// Hoster of ROMs
struct hoster_s {
    char *fullname;
    uint8_t active;
    char *name;
    struct cache_s *cacheHandler;
    struct memimage_s *favicon;

    acll_t *(*search)(system_t *system, char *searchString);

    void (*download)(result_t *item, downloadCallback_t downloadCallbackFunction, void *appData);
};

// Search Result
struct result_s {
    char *title;
    uint8_t active;
    char *url;
    float rating;
    int32_t downloads;
    char *fileSize;
    system_t *system;
    hoster_t *hoster;
};

// Caching of search results or hoster's content
struct cache_s {
    void *appData;

    uint8_t (*isValid)(struct hoster_s *hoster, struct system_s *system, void *appData);

    void (*clear)(struct hoster_s *hoster, struct system_s *system, void *appData);

    void (*add)(struct hoster_s *hoster, struct system_s *system, char *searchString, result_t *entry, void *appData);

    acll_t *(*get)(struct hoster_s *hoster, struct system_s *system, char *searchString, void *appData);

    void (*touch)(struct hoster_s *hoster, struct system_s *system, void *appData);
};

// Definition of a http response
struct http_response_s {
    size_t size;
    char *data;
};

// Exported methods
acll_t *systems_init();

void systems_destroy(acll_t *systems);

int system_findByFullname(void *payload, void *input);

acll_t *hosterhandler_init(cache_t *cacheHandler);

acll_t *hosterhandler_search(acll_t *hosters, system_t *system, char *searchString);

void hosterhandler_download(result_t *item, downloadCallback_t downloadCallbackFunction, void *appData);

void hosterhandler_destroy(acll_t *hoster);

int hoster_findByFullname(void *payload, void *input);

int hoster_findByName(void *payload, void *input);

void result_freeList(acll_t *resultList);

int http_download(char *url, char *data, httpmethod_t method, char *filename, curl_off_t *current, curl_off_t *total,
                  volatile uint8_t *cancellation);

http_response_t *http_fetch(char *url, char *postData, httpmethod_t method, long ignoreHeaders);

void http_freeResponse(http_response_t *response);

// nice macros for method calling
#define loadSystems systems_init
#define findSystemByFullname(systems, fullname) acll_find(systems, system_findByFullname, fullname)
#define getSystem(system) ((system_t *) system->payload)
#define destroySystems(systems) systems_destroy(systems)

#define loadHosters hosterhandler_init
#define getHoster(hoster) ((hoster_t *) hoster->payload)
#define findHosterByFullname(hosters, fullname) acll_find(hosters, hoster_findByFullname, fullname)
#define findHosterByName(hosters, name) acll_find(hosters, hoster_findByName, name)

#define destroyHosters(hosters) hosterhandler_destroy(hosters)
#define searchHosters(hosters, system, searchString) hosterhandler_search(hosters, system, searchString)
#define downloadItem(item, downloadCallbackFunction, appData) hosterhandler_download(item, downloadCallbackFunction, appData)
#define destroyResults(results) result_freeList(results)

#define getResult(result) ((result_t *) result->payload)

// define the number of parallel threads to fetch content from hosters
#ifndef HOSTER_FETCH_THREADS
#define HOSTER_FETCH_THREADS 5
#endif

// default loglevel
#ifndef LOG_LEVEL
#define LOG_LEVEL 2
#endif

// log output
#ifndef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) if ( LOG_LEVEL > 1) { printf("\nDEBUG: "); printf(fmt, ##__VA_ARGS__);}
#endif

#ifndef LOG_INFO
#define LOG_INFO(fmt, ...) if ( LOG_LEVEL > 0 ) { printf("\nINFO: "); printf(fmt, ##__VA_ARGS__); }
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(fmt, ...) { printf("\nERROR: "); printf(fmt, ##__VA_ARGS__);}
#endif

#endif
