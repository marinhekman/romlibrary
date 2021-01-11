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

#include <csafestring.h>
#include <hoster/results.h>
#include "enginecache.h"
#include <romlibrary.h>
#include <common/utils.h>

static void deleteTimestamp(sqlite3 *db, hoster_t *hoster, system_t *system);

static void insertTimestamp(sqlite3 *db, hoster_t *hoster, system_t *system);

void enginecache_init(sqlite3 *db) {
    char *err_msg = 0;

    char *query = "CREATE TABLE enginecache (hosters TEXT, system TEXT, title TEXT, url TEXT, downloads INT, fileSize TEXT, rating REAL)";
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        LOG_ERROR("Failed to create table - SQL error: %s", err_msg);
        sqlite3_free(err_msg);
    }

    query = "CREATE INDEX enginecache_idx ON enginecache (hosters, title)";
    rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        LOG_ERROR("Failed to create index - SQL error: %s", err_msg);
        sqlite3_free(err_msg);
    }
}

void enginecache_initstate(sqlite3 *db) {
    char *err_msg = 0;

    char *query = "CREATE TABLE enginecachestate (hosters TEXT, system TEXT, time INT64)";
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        LOG_ERROR("Failed to create table - SQL error: %s", err_msg);
        sqlite3_free(err_msg);
    }
}

void enginecache_clear(hoster_t *hoster, system_t *system, void *data) {
    sqlite3 *db = data;
    char *query = "DELETE FROM enginecache WHERE hosters=@hosters AND system=@system";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);
    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        LOG_ERROR("delete statement didn't return DONE (%i): %s", rc, sqlite3_errmsg(db));
    }
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
}

uint8_t enginecache_isCacheValid(hoster_t *hoster, system_t *system, void *data) {
    sqlite3 *db = data;
    char *query = "SELECT time FROM enginecachestate WHERE hosters=@hosters AND system=@system";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);
    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        int timer = sqlite3_column_int(stmt, 0);
        if (timer > time(NULL) - 3600 * 24 * 30) {
            sqlite3_finalize(stmt);
            return 1;
        }
        LOG_INFO("Search cache for %s / %s invalidated", hoster->name, system->name);
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_finalize(stmt);
    return 0;
}

void enginecache_addEntry(hoster_t *hoster, system_t *system, result_t *entry, void *data) {
    sqlite3 *db = data;
    char *query = "INSERT INTO enginecache (hosters, system, title, url, downloads, fileSize, rating) VALUES (@hosters, @system, @title, @url, @downloads, @fileSize, @rating)";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@title");
        sqlite3_bind_text(stmt, idx, entry->title, strlen(entry->title), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@url");
        sqlite3_bind_text(stmt, idx, entry->url, strlen(entry->url), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@downloads");
        sqlite3_bind_int(stmt, idx, entry->downloads);

        if (entry->fileSize != NULL) {
            idx = sqlite3_bind_parameter_index(stmt, "@fileSize");
            sqlite3_bind_text(stmt, idx, entry->fileSize, strlen(entry->fileSize), NULL);
        }

        idx = sqlite3_bind_parameter_index(stmt, "@rating");
        sqlite3_bind_int(stmt, idx, entry->downloads);
        sqlite3_bind_double(stmt, idx, entry->rating);
    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        LOG_ERROR("insert statement didn't return DONE (%i): %s", rc, sqlite3_errmsg(db));
    }
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
}

void enginecache_updateTimestamp(hoster_t *hoster, system_t *system, void *data) {
    deleteTimestamp(data, hoster, system);
    insertTimestamp(data, hoster, system);
}

acll_t *enginecache_getSearchResults(hoster_t *hoster, system_t *system, char *searchString, void *data) {
    sqlite3 *db = data;
    char *query = "SELECT title, url, downloads, fileSize, rating FROM enginecache WHERE hosters=@hosters AND system=@system AND UPPER(title) LIKE @searchString";

    sqlite3_stmt *stmt;
    char *tmp = NULL;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);

        tmp = (char *) calloc(strlen(searchString) + 3, sizeof(char));
        tmp[0] = '%';
        strcpy(&tmp[1], searchString);
        tmp[strlen(tmp)] = '%';

        idx = sqlite3_bind_parameter_index(stmt, "@searchString");
        sqlite3_bind_text(stmt, idx, tmp, strlen(tmp), NULL);

    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    acll_t *resultList = NULL;
    int ret = sqlite3_step(stmt);
    while (ret == SQLITE_ROW) {
        result_t *item = result_newItem(system, hoster);
        result_setTitle(item, (char *) sqlite3_column_text(stmt, 0));
        result_setUrl(item, (char *) sqlite3_column_text(stmt, 1));
        result_setFileSize(item, (char *) sqlite3_column_text(stmt, 3));
        item->downloads = sqlite3_column_int(stmt, 2);
        item->rating = sqlite3_column_double(stmt, 4);
        resultList = acll_push(resultList, item);
        ret = sqlite3_step(stmt);
    }
    if (ret == SQLITE_ERROR) {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
    FREENOTNULL(tmp);
    return resultList;
}

static void deleteTimestamp(sqlite3 *db, hoster_t *hoster, system_t *system) {
    char *query = "DELETE FROM enginecachestate WHERE hosters=@hosters AND system=@system";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);

    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        LOG_ERROR("delete statement didn't return DONE (%i): %s", rc, sqlite3_errmsg(db));
    }
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
}

static void insertTimestamp(sqlite3 *db, hoster_t *hoster, system_t *system) {
    char *query = "INSERT INTO enginecachestate (hosters, system, time) VALUES (@hosters, @system, @time)";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int idx;
        idx = sqlite3_bind_parameter_index(stmt, "@hosters");
        sqlite3_bind_text(stmt, idx, hoster->name, strlen(hoster->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@system");
        sqlite3_bind_text(stmt, idx, system->name, strlen(system->name), NULL);

        idx = sqlite3_bind_parameter_index(stmt, "@time");
        sqlite3_bind_int64(stmt, idx, time(NULL));
    } else {
        LOG_ERROR("Failed to execute statement: %s", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        LOG_ERROR("insert statement didn't return DONE (%i): %s", rc, sqlite3_errmsg(db));
    }
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
}