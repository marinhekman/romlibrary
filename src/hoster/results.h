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

#ifndef ENGINE_RESULTS_H
#define ENGINE_RESULTS_H

#include <romlibrary.h>

result_t *result_create(system_t *system, hoster_t *hoster, char *title, char *url);

void result_setTitle(result_t *result, char *title);

void result_setUrl(result_t *result, char *url);

void result_setDownloads(result_t *result, char *downloads);

void result_setRating(result_t *result, char *rating, uint8_t maxRating);

void result_setFileSize(result_t *result, char *fileSize);

void result_freeList(acll_t *results);

acll_t *result_sort(acll_t *results);

#endif
