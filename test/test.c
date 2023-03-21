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

#include <sqlite3.h>
#include "test.h"
#include "hoster_freeroms.h"
#include "hoster_romhustler.h"
#include "systems.h"
#include "hoster.h"
#include "enginecache.h"
#include "hoster_romsdownload.h"
#include "hoster_wowroms.h"

int main(int argc, char **argv) {
    sqlite3 *db;
    if (sqlite3_open_v2(":memory:", &db,
                        SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK) {
        printf("Could not initialize database in memory: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    enginecache_init(db);
    enginecache_initstate(db);

    testsystems_init();
    testengines_init(db);

    TESTCALL("test_engine_freeroms_3do", test_engine_freeroms_3do, NULL);
    TESTCALL("test_engine_freeroms_amiga", test_engine_freeroms_amiga, NULL);
    TESTCALL("test_engine_freeroms_atari2600", test_engine_freeroms_atari2600, NULL);
    TESTCALL("test_engine_freeroms_atari7800", test_engine_freeroms_atari7800, NULL);
    TESTCALL("test_engine_freeroms_atarijaguar", test_engine_freeroms_atarijaguar, NULL);
    TESTCALL("test_engine_freeroms_atarilynx", test_engine_freeroms_atarilynx, NULL);
    TESTCALL("test_engine_freeroms_atarist", test_engine_freeroms_atarist, NULL);
    TESTCALL("test_engine_freeroms_c64", test_engine_freeroms_c64, NULL);
    TESTCALL("test_engine_freeroms_dreamcast", test_engine_freeroms_dreamcast, NULL);
    TESTCALL("test_engine_freeroms_fba", test_engine_freeroms_fba, NULL);
    TESTCALL("test_engine_freeroms_fds", test_engine_freeroms_fds, NULL);
    TESTCALL("test_engine_freeroms_gamegear", test_engine_freeroms_gamegear, NULL);
    TESTCALL("test_engine_freeroms_gb", test_engine_freeroms_gb, NULL);
    TESTCALL("test_engine_freeroms_gba", test_engine_freeroms_gba, NULL);
    TESTCALL("test_engine_freeroms_gbc", test_engine_freeroms_gbc, NULL);
    TESTCALL("test_engine_freeroms_gc", test_engine_freeroms_gc, NULL);
    TESTCALL("test_engine_freeroms_genesis", test_engine_freeroms_genesis, NULL);
    TESTCALL("test_engine_freeroms_gw", test_engine_freeroms_gw, NULL);
    TESTCALL("test_engine_freeroms_love", test_engine_freeroms_love, NULL);
    TESTCALL("test_engine_freeroms_mame", test_engine_freeroms_mame, NULL);
    TESTCALL("test_engine_freeroms_mastersystem", test_engine_freeroms_mastersystem, NULL);
    TESTCALL("test_engine_freeroms_megadrive", test_engine_freeroms_megadrive, NULL);
    TESTCALL("test_engine_freeroms_msx", test_engine_freeroms_msx, NULL);
    TESTCALL("test_engine_freeroms_n64", test_engine_freeroms_n64, NULL);
    TESTCALL("test_engine_freeroms_nds", test_engine_freeroms_nds, NULL);
    TESTCALL("test_engine_freeroms_neogeo", test_engine_freeroms_neogeo, NULL);
    TESTCALL("test_engine_freeroms_nes", test_engine_freeroms_nes, NULL);
    TESTCALL("test_engine_freeroms_ngp", test_engine_freeroms_ngp, NULL);
    TESTCALL("test_engine_freeroms_ngpc", test_engine_freeroms_ngpc, NULL);
    TESTCALL("test_engine_freeroms_pc", test_engine_freeroms_pc, NULL);
    TESTCALL("test_engine_freeroms_pcengine", test_engine_freeroms_pcengine, NULL);
    TESTCALL("test_engine_freeroms_pcfx", test_engine_freeroms_pcfx, NULL);
    TESTCALL("test_engine_freeroms_ps2", test_engine_freeroms_ps2, NULL);
    TESTCALL("test_engine_freeroms_psp", test_engine_freeroms_psp, NULL);
    TESTCALL("test_engine_freeroms_psx", test_engine_freeroms_psx, NULL);
    TESTCALL("test_engine_freeroms_saturn", test_engine_freeroms_saturn, NULL);
    TESTCALL("test_engine_freeroms_scummvm", test_engine_freeroms_scummvm, NULL);
    TESTCALL("test_engine_freeroms_sega32x", test_engine_freeroms_sega32x, NULL);
    TESTCALL("test_engine_freeroms_segacd", test_engine_freeroms_segacd, NULL);
    TESTCALL("test_engine_freeroms_sg1000", test_engine_freeroms_sg1000, NULL);
    TESTCALL("test_engine_freeroms_snes", test_engine_freeroms_snes, NULL);
    TESTCALL("test_engine_freeroms_vectrex", test_engine_freeroms_vectrex, NULL);
    TESTCALL("test_engine_freeroms_videopac", test_engine_freeroms_videopac, NULL);
    TESTCALL("test_engine_freeroms_virtualboy", test_engine_freeroms_virtualboy, NULL);
    TESTCALL("test_engine_freeroms_wii", test_engine_freeroms_wii, NULL);
    TESTCALL("test_engine_freeroms_wiiu", test_engine_freeroms_wiiu, NULL);
    TESTCALL("test_engine_freeroms_wonderswan", test_engine_freeroms_wonderswan, NULL);
    TESTCALL("test_engine_freeroms_wonderswancolor", test_engine_freeroms_wonderswancolor, NULL);
    TESTCALL("test_engine_freeroms_zxspectrum", test_engine_freeroms_zxspectrum, NULL);
    TESTCALL("test_engine_freeroms_download", test_engine_freeroms_download, NULL);

    TESTCALL("test_engine_romhustler_3do", test_engine_romhustler_3do, NULL);
    TESTCALL("test_engine_romhustler_amiga", test_engine_romhustler_amiga, NULL);
    TESTCALL("test_engine_romhustler_atari2600", test_engine_romhustler_atari2600, NULL);
    TESTCALL("test_engine_romhustler_atari7800", test_engine_romhustler_atari7800, NULL);
    TESTCALL("test_engine_romhustler_atarijaguar", test_engine_romhustler_atarijaguar, NULL);
    TESTCALL("test_engine_romhustler_atarilynx", test_engine_romhustler_atarilynx, NULL);
    TESTCALL("test_engine_romhustler_atarist", test_engine_romhustler_atarist, NULL);
    TESTCALL("test_engine_romhustler_c64", test_engine_romhustler_c64, NULL);
    TESTCALL("test_engine_romhustler_dreamcast", test_engine_romhustler_dreamcast, NULL);
    TESTCALL("test_engine_romhustler_fba", test_engine_romhustler_fba, NULL);
    TESTCALL("test_engine_romhustler_fds", test_engine_romhustler_fds, NULL);
    TESTCALL("test_engine_romhustler_gamegear", test_engine_romhustler_gamegear, NULL);
    TESTCALL("test_engine_romhustler_gb", test_engine_romhustler_gb, NULL);
    TESTCALL("test_engine_romhustler_gba", test_engine_romhustler_gba, NULL);
    TESTCALL("test_engine_romhustler_gbc", test_engine_romhustler_gbc, NULL);
    TESTCALL("test_engine_romhustler_gc", test_engine_romhustler_gc, NULL);
    TESTCALL("test_engine_romhustler_genesis", test_engine_romhustler_genesis, NULL);
    TESTCALL("test_engine_romhustler_gw", test_engine_romhustler_gw, NULL);
    TESTCALL("test_engine_romhustler_love", test_engine_romhustler_love, NULL);
    TESTCALL("test_engine_romhustler_mame", test_engine_romhustler_mame, NULL);
    TESTCALL("test_engine_romhustler_mastersystem", test_engine_romhustler_mastersystem, NULL);
    TESTCALL("test_engine_romhustler_megadrive", test_engine_romhustler_megadrive, NULL);
    TESTCALL("test_engine_romhustler_msx", test_engine_romhustler_msx, NULL);
    TESTCALL("test_engine_romhustler_n64", test_engine_romhustler_n64, NULL);
    TESTCALL("test_engine_romhustler_nds", test_engine_romhustler_nds, NULL);
    TESTCALL("test_engine_romhustler_neogeo", test_engine_romhustler_neogeo, NULL);
    TESTCALL("test_engine_romhustler_nes", test_engine_romhustler_nes, NULL);
    TESTCALL("test_engine_romhustler_ngp", test_engine_romhustler_ngp, NULL);
    TESTCALL("test_engine_romhustler_ngpc", test_engine_romhustler_ngpc, NULL);
    TESTCALL("test_engine_romhustler_pc", test_engine_romhustler_pc, NULL);
    TESTCALL("test_engine_romhustler_pcengine", test_engine_romhustler_pcengine, NULL);
    TESTCALL("test_engine_romhustler_pcfx", test_engine_romhustler_pcfx, NULL);
    TESTCALL("test_engine_romhustler_ps2", test_engine_romhustler_ps2, NULL);
    TESTCALL("test_engine_romhustler_psp", test_engine_romhustler_psp, NULL);
    TESTCALL("test_engine_romhustler_psx", test_engine_romhustler_psx, NULL);
    TESTCALL("test_engine_romhustler_saturn", test_engine_romhustler_saturn, NULL);
    TESTCALL("test_engine_romhustler_scummvm", test_engine_romhustler_scummvm, NULL);
    TESTCALL("test_engine_romhustler_sega32x", test_engine_romhustler_sega32x, NULL);
    TESTCALL("test_engine_romhustler_segacd", test_engine_romhustler_segacd, NULL);
    TESTCALL("test_engine_romhustler_sg1000", test_engine_romhustler_sg1000, NULL);
    TESTCALL("test_engine_romhustler_snes", test_engine_romhustler_snes, NULL);
    TESTCALL("test_engine_romhustler_vectrex", test_engine_romhustler_vectrex, NULL);
    TESTCALL("test_engine_romhustler_videopac", test_engine_romhustler_videopac, NULL);
    TESTCALL("test_engine_romhustler_virtualboy", test_engine_romhustler_virtualboy, NULL);
    TESTCALL("test_engine_romhustler_wii", test_engine_romhustler_wii, NULL);
    TESTCALL("test_engine_romhustler_wiiu", test_engine_romhustler_wiiu, NULL);
    TESTCALL("test_engine_romhustler_wonderswan", test_engine_romhustler_wonderswan, NULL);
    TESTCALL("test_engine_romhustler_wonderswancolor", test_engine_romhustler_wonderswancolor, NULL);
    TESTCALL("test_engine_romhustler_zxspectrum", test_engine_romhustler_zxspectrum, NULL);
    TESTCALL("test_engine_romhustler_download", test_engine_romhustler_download, NULL);

    TESTCALL("test_engine_romsdownload_3do", test_engine_romsdownload_3do, NULL);
    TESTCALL("test_engine_romsdownload_amiga", test_engine_romsdownload_amiga, NULL);
    TESTCALL("test_engine_romsdownload_atari2600", test_engine_romsdownload_atari2600, NULL);
    TESTCALL("test_engine_romsdownload_atari7800", test_engine_romsdownload_atari7800, NULL);
    TESTCALL("test_engine_romsdownload_atarijaguar", test_engine_romsdownload_atarijaguar, NULL);
    TESTCALL("test_engine_romsdownload_atarilynx", test_engine_romsdownload_atarilynx, NULL);
    TESTCALL("test_engine_romsdownload_atarist", test_engine_romsdownload_atarist, NULL);
    TESTCALL("test_engine_romsdownload_c64", test_engine_romsdownload_c64, NULL);
    TESTCALL("test_engine_romsdownload_dreamcast", test_engine_romsdownload_dreamcast, NULL);
    TESTCALL("test_engine_romsdownload_fba", test_engine_romsdownload_fba, NULL);
    TESTCALL("test_engine_romsdownload_fds", test_engine_romsdownload_fds, NULL);
    TESTCALL("test_engine_romsdownload_gamegear", test_engine_romsdownload_gamegear, NULL);
    TESTCALL("test_engine_romsdownload_gb", test_engine_romsdownload_gb, NULL);
    TESTCALL("test_engine_romsdownload_gba", test_engine_romsdownload_gba, NULL);
    TESTCALL("test_engine_romsdownload_gbc", test_engine_romsdownload_gbc, NULL);
    TESTCALL("test_engine_romsdownload_gc", test_engine_romsdownload_gc, NULL);
    TESTCALL("test_engine_romsdownload_genesis", test_engine_romsdownload_genesis, NULL);
    TESTCALL("test_engine_romsdownload_gw", test_engine_romsdownload_gw, NULL);
    TESTCALL("test_engine_romsdownload_love", test_engine_romsdownload_love, NULL);
    TESTCALL("test_engine_romsdownload_mame", test_engine_romsdownload_mame, NULL);
    TESTCALL("test_engine_romsdownload_mastersystem", test_engine_romsdownload_mastersystem, NULL);
    TESTCALL("test_engine_romsdownload_megadrive", test_engine_romsdownload_megadrive, NULL);
    TESTCALL("test_engine_romsdownload_msx", test_engine_romsdownload_msx, NULL);
    TESTCALL("test_engine_romsdownload_n64", test_engine_romsdownload_n64, NULL);
    TESTCALL("test_engine_romsdownload_nds", test_engine_romsdownload_nds, NULL);
    TESTCALL("test_engine_romsdownload_neogeo", test_engine_romsdownload_neogeo, NULL);
    TESTCALL("test_engine_romsdownload_nes", test_engine_romsdownload_nes, NULL);
    TESTCALL("test_engine_romsdownload_ngp", test_engine_romsdownload_ngp, NULL);
    TESTCALL("test_engine_romsdownload_ngpc", test_engine_romsdownload_ngpc, NULL);
    TESTCALL("test_engine_romsdownload_pc", test_engine_romsdownload_pc, NULL);
    TESTCALL("test_engine_romsdownload_pcengine", test_engine_romsdownload_pcengine, NULL);
    TESTCALL("test_engine_romsdownload_pcfx", test_engine_romsdownload_pcfx, NULL);
    TESTCALL("test_engine_romsdownload_ps2", test_engine_romsdownload_ps2, NULL);
    TESTCALL("test_engine_romsdownload_psp", test_engine_romsdownload_psp, NULL);
    TESTCALL("test_engine_romsdownload_psx", test_engine_romsdownload_psx, NULL);
    TESTCALL("test_engine_romsdownload_saturn", test_engine_romsdownload_saturn, NULL);
    TESTCALL("test_engine_romsdownload_scummvm", test_engine_romsdownload_scummvm, NULL);
    TESTCALL("test_engine_romsdownload_sega32x", test_engine_romsdownload_sega32x, NULL);
    TESTCALL("test_engine_romsdownload_segacd", test_engine_romsdownload_segacd, NULL);
    TESTCALL("test_engine_romsdownload_sg1000", test_engine_romsdownload_sg1000, NULL);
    TESTCALL("test_engine_romsdownload_snes", test_engine_romsdownload_snes, NULL);
    TESTCALL("test_engine_romsdownload_vectrex", test_engine_romsdownload_vectrex, NULL);
    TESTCALL("test_engine_romsdownload_videopac", test_engine_romsdownload_videopac, NULL);
    TESTCALL("test_engine_romsdownload_virtualboy", test_engine_romsdownload_virtualboy, NULL);
    TESTCALL("test_engine_romsdownload_wii", test_engine_romsdownload_wii, NULL);
    TESTCALL("test_engine_romsdownload_wiiu", test_engine_romsdownload_wiiu, NULL);
    TESTCALL("test_engine_romsdownload_wonderswan", test_engine_romsdownload_wonderswan, NULL);
    TESTCALL("test_engine_romsdownload_wonderswancolor", test_engine_romsdownload_wonderswancolor, NULL);
    TESTCALL("test_engine_romsdownload_zxspectrum", test_engine_romsdownload_zxspectrum, NULL);
    TESTCALL("test_engine_romsdownload_download", test_engine_romsdownload_download, NULL);

    TESTCALL("test_engine_wowroms_3do", test_engine_wowroms_3do, NULL);
    TESTCALL("test_engine_wowroms_amiga", test_engine_wowroms_amiga, NULL);
    TESTCALL("test_engine_wowroms_atari2600", test_engine_wowroms_atari2600, NULL);
    TESTCALL("test_engine_wowroms_atari7800", test_engine_wowroms_atari7800, NULL);
    TESTCALL("test_engine_wowroms_atarijaguar", test_engine_wowroms_atarijaguar, NULL);
    TESTCALL("test_engine_wowroms_atarilynx", test_engine_wowroms_atarilynx, NULL);
    TESTCALL("test_engine_wowroms_atarist", test_engine_wowroms_atarist, NULL);
    TESTCALL("test_engine_wowroms_c64", test_engine_wowroms_c64, NULL);
    TESTCALL("test_engine_wowroms_dreamcast", test_engine_wowroms_dreamcast, NULL);
    TESTCALL("test_engine_wowroms_fba", test_engine_wowroms_fba, NULL);
    TESTCALL("test_engine_wowroms_fds", test_engine_wowroms_fds, NULL);
    TESTCALL("test_engine_wowroms_gamegear", test_engine_wowroms_gamegear, NULL);
    TESTCALL("test_engine_wowroms_gb", test_engine_wowroms_gb, NULL);
    TESTCALL("test_engine_wowroms_gba", test_engine_wowroms_gba, NULL);
    TESTCALL("test_engine_wowroms_gbc", test_engine_wowroms_gbc, NULL);
    TESTCALL("test_engine_wowroms_gc", test_engine_wowroms_gc, NULL);
    TESTCALL("test_engine_wowroms_genesis", test_engine_wowroms_genesis, NULL);
    TESTCALL("test_engine_wowroms_gw", test_engine_wowroms_gw, NULL);
    TESTCALL("test_engine_wowroms_love", test_engine_wowroms_love, NULL);
    TESTCALL("test_engine_wowroms_mame", test_engine_wowroms_mame, NULL);
    TESTCALL("test_engine_wowroms_mastersystem", test_engine_wowroms_mastersystem, NULL);
    TESTCALL("test_engine_wowroms_megadrive", test_engine_wowroms_megadrive, NULL);
    TESTCALL("test_engine_wowroms_msx", test_engine_wowroms_msx, NULL);
    TESTCALL("test_engine_wowroms_n64", test_engine_wowroms_n64, NULL);
    TESTCALL("test_engine_wowroms_nds", test_engine_wowroms_nds, NULL);
    TESTCALL("test_engine_wowroms_neogeo", test_engine_wowroms_neogeo, NULL);
    TESTCALL("test_engine_wowroms_nes", test_engine_wowroms_nes, NULL);
    TESTCALL("test_engine_wowroms_ngp", test_engine_wowroms_ngp, NULL);
    TESTCALL("test_engine_wowroms_ngpc", test_engine_wowroms_ngpc, NULL);
    TESTCALL("test_engine_wowroms_pc", test_engine_wowroms_pc, NULL);
    TESTCALL("test_engine_wowroms_pcengine", test_engine_wowroms_pcengine, NULL);
    TESTCALL("test_engine_wowroms_pcfx", test_engine_wowroms_pcfx, NULL);
    TESTCALL("test_engine_wowroms_ps2", test_engine_wowroms_ps2, NULL);
    TESTCALL("test_engine_wowroms_psp", test_engine_wowroms_psp, NULL);
    TESTCALL("test_engine_wowroms_psx", test_engine_wowroms_psx, NULL);
    TESTCALL("test_engine_wowroms_saturn", test_engine_wowroms_saturn, NULL);
    TESTCALL("test_engine_wowroms_scummvm", test_engine_wowroms_scummvm, NULL);
    TESTCALL("test_engine_wowroms_sega32x", test_engine_wowroms_sega32x, NULL);
    TESTCALL("test_engine_wowroms_segacd", test_engine_wowroms_segacd, NULL);
    TESTCALL("test_engine_wowroms_sg1000", test_engine_wowroms_sg1000, NULL);
    TESTCALL("test_engine_wowroms_snes", test_engine_wowroms_snes, NULL);
    TESTCALL("test_engine_wowroms_vectrex", test_engine_wowroms_vectrex, NULL);
    TESTCALL("test_engine_wowroms_videopac", test_engine_wowroms_videopac, NULL);
    TESTCALL("test_engine_wowroms_virtualboy", test_engine_wowroms_virtualboy, NULL);
    TESTCALL("test_engine_wowroms_wii", test_engine_wowroms_wii, NULL);
    TESTCALL("test_engine_wowroms_wiiu", test_engine_wowroms_wiiu, NULL);
    TESTCALL("test_engine_wowroms_wonderswan", test_engine_wowroms_wonderswan, NULL);
    TESTCALL("test_engine_wowroms_wonderswancolor", test_engine_wowroms_wonderswancolor, NULL);
    TESTCALL("test_engine_wowroms_zxspectrum", test_engine_wowroms_zxspectrum, NULL);
    TESTCALL("test_engine_wowroms_download", test_engine_wowroms_download, NULL);

    sqlite3_close(db);
    testsystems_destroy();
    return 0;
}

int resultFilter(void *payload, void *input) {
    rl_result *result = payload;
    return !strcmp(result->title, (char *) input);
}