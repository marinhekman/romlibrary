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

#ifndef TEST_HOSTER_H
#define TEST_HOSTER_H

#include <romlibrary.h>
#include <sqlite3.h>

hoster_t *romsmania;
hoster_t *romsmode;
hoster_t *wowroms;
hoster_t *romsdownload;
hoster_t *romsemulator;
hoster_t *romhustler;
hoster_t *freeroms;

void testengines_init(sqlite3 *db);

#endif
