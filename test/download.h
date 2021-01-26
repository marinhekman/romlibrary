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

#ifndef TEST_DOWNLOAD_H
#define TEST_DOWNLOAD_H

#include <romlibrary.h>

typedef struct test_downloaddata_s {
    rl_system *system;
    char *title;
    char *url;
    char *data;
    char *filename;
    chttp_method method;
} test_downloaddata_t;

uint8_t testDownloadCallback(void *appData, rl_system *system, char *title, char *url, char *data, char *filename,
                             chttp_method method);

#endif
