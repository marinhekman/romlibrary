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
#include "hoster.h"
#include "enginecache.h"

rl_cache cacheHandler;

void testengines_init(sqlite3 *db) {
    cacheHandler.data = db;
    cacheHandler.isValid = enginecache_isCacheValid;
    cacheHandler.clear = enginecache_clear;
    cacheHandler.add = enginecache_addEntry;
    cacheHandler.touch = enginecache_updateTimestamp;
    cacheHandler.get = enginecache_getSearchResults;

    acll_t *hosters = rl_hoster_init(&cacheHandler);

    romhustler = rl_getHoster(rl_hosters_findByFullname(hosters, "https://romhustler.org"));
    freeroms = rl_getHoster(rl_hosters_findByFullname(hosters, "https://freeroms.com"));
    romsdownload = rl_getHoster(rl_hosters_findByFullname(hosters, "https://www.roms-download.com"));
    wowroms = rl_getHoster(rl_hosters_findByFullname(hosters, "https://www.wowroms.com"));
}