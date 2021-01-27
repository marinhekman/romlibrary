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
#include <romlibrary.h>
#include "test.h"
#include "systems.h"
#include "hoster.h"
#include "download.h"

static int run_test_active(rl_system *system, char *searchString, char *includedTitle);

static int run_test_inactive(rl_system *system);

int test_engine_freeroms_3do() {
    return run_test_inactive(threeDo);
}

int test_engine_freeroms_amiga() {
    return run_test_active(amiga, "DAMAGE", "Damage");
}

int test_engine_freeroms_atari2600() {
    return run_test_active(atari2600, "PENGO", "Pengo");
}

int test_engine_freeroms_atari7800() {
    return run_test_active(atari7800, "GHOST MANOR", "Ghost Manor");
}

int test_engine_freeroms_atarijaguar() {
    return run_test_active(atarijaguar, "NBA", "NBA Jam TE (1996)");
}

int test_engine_freeroms_atarilynx() {
    return run_test_active(atarilynx, "Conners Tennis", "Jimmy Conners Tennis (1991)");
}

int test_engine_freeroms_atarist() {
    return run_test_inactive(atarist);
}

int test_engine_freeroms_c64() {
    return run_test_inactive(c64);
}

int test_engine_freeroms_dreamcast() {
    return run_test_active(dreamcast, "Dalmations To The Rescue", "101 Dalmations To The Rescue");
}

int test_engine_freeroms_fba() {
    return run_test_inactive(fba);
}

int test_engine_freeroms_fds() {
    return run_test_active(fds, "Z-Gunda", "Z-Gundam");
}

int test_engine_freeroms_gamegear() {
    return run_test_active(gamegear, "Excellent Dizzy", "Excellent Dizzy");
}

int test_engine_freeroms_gb() {
    return run_test_active(gb, "Oide Rascal", "Oide Rascal (Japan)");
}

int test_engine_freeroms_gba() {
    return run_test_active(gba, "Helsing", "Van Helsing");
}

int test_engine_freeroms_gbc() {
    return run_test_active(gbc, "Olympic Summer", "Olympic Summer Games");
}

int test_engine_freeroms_gc() {
    return run_test_active(gc, "Sorcerers Stone", "Harry Potter and the Sorcerers Stone");
}

int test_engine_freeroms_genesis() {
    return run_test_active(genesis, "NBA Jam", "NBA Jam Tournament Edition (32X)");
}

int test_engine_freeroms_gw() {
    return run_test_inactive(gw);
}

int test_engine_freeroms_love() {
    return run_test_inactive(love);
}

int test_engine_freeroms_mame() {
    return run_test_active(mame, "Quadro Quiz", "Quadro Quiz II");
}

int test_engine_freeroms_mastersystem() {
    return run_test_active(mastersystem, "Out Run 3D", "Out Run 3D");
}

int test_engine_freeroms_megadrive() {
    return run_test_active(megadrive, "NBA Jam", "NBA Jam Tournament Edition (32X)");
}

int test_engine_freeroms_msx() {
    return run_test_inactive(msx);
}

int test_engine_freeroms_n64() {
    return run_test_active(n64, "Mario Kart", "Mario Kart 64");
}

int test_engine_freeroms_nds() {
    return run_test_active(nds, "Mario and Luigi Partners in Time Europe", "Mario and Luigi Partners in Time Europe");
}

int test_engine_freeroms_neogeo() {
    return run_test_active(neogeo, "Infinity Cure", "Infinity Cure (J) [!]");
}

int test_engine_freeroms_nes() {
    return run_test_active(nes, "Z-Gunda", "Z-Gundam");
}

int test_engine_freeroms_ngp() {
    return run_test_active(ngp, "Wrestling Madness", "Wrestling Madness (Beta)");
}

int test_engine_freeroms_ngpc() {
    return run_test_active(ngpc, "Magical Drop Pocket Hack", "Magical Drop Pocket Hack");
}

int test_engine_freeroms_pc() {
    return run_test_inactive(pc);
}

int test_engine_freeroms_pcengine() {
    return run_test_inactive(pcengine);
}

int test_engine_freeroms_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_freeroms_ps2() {
    return run_test_inactive(ps2);
}

int test_engine_freeroms_psp() {
    return run_test_active(psp, "Qix", "Qix++ Japan");
}

int test_engine_freeroms_psx() {
    return run_test_active(psx, "Panzer Front", "Panzer Front");
}

int test_engine_freeroms_saturn() {
    return run_test_inactive(saturn);
}

int test_engine_freeroms_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_freeroms_sega32x() {
    return run_test_inactive(sega32x);
}

int test_engine_freeroms_segacd() {
    return run_test_active(segacd, "NBA Jam", "NBA Jam Tournament Edition (32X)");
}

int test_engine_freeroms_sg1000() {
    return run_test_inactive(sg1000);
}

int test_engine_freeroms_snes() {
    return run_test_active(snes, "Q-bert", "Q-bert 3");
}

int test_engine_freeroms_vectrex() {
    return run_test_inactive(vectrex);
}

int test_engine_freeroms_videopac() {
    return run_test_inactive(videopac);
}

int test_engine_freeroms_virtualboy() {
    return run_test_inactive(virtualboy);
}

int test_engine_freeroms_wii() {
    return run_test_inactive(wii);
}

int test_engine_freeroms_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_freeroms_wonderswan() {
    return run_test_active(wonderswan, "Tetsuman", "Tetsuman (J) [M][!]");
}

int test_engine_freeroms_wonderswancolor() {
    return run_test_inactive(wonderswancolor);
}

int test_engine_freeroms_zxspectrum() {
    return run_test_inactive(zxspectrum);
}

int test_engine_freeroms_download() {
    acll_t *list = freeroms->search(amiga, "DAMAGE");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Damage");
    ASSERTSTR("Damage", rl_getResult(list)->title);


    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Damage.zip";
    testdata->title = "Damage";
    testdata->system = amiga;
    testdata->data = NULL;
    testdata->url = "https://www.freeroms.com/dl_roms/rom_download_tr.php?system=amiga&game_id=10579";

    freeroms->download(rl_getResult(list), testDownloadCallback, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = freeroms->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = freeroms->search(system, "");
    ASSERTNULL(list);
    return 0;
}