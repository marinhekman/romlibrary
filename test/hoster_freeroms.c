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

int test_engine_freeroms_3do() {
    acll_t *list = freeroms->search(threeDo, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_amiga() {
    acll_t *list = freeroms->search(amiga, "DAMAGE");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Damage", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_atari2600() {
    acll_t *list = freeroms->search(atari2600, "PENGO");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Pengo", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_atari7800() {
    acll_t *list = freeroms->search(atari7800, "GHOST MANOR");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Ghost Manor", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_atarijaguar() {
    acll_t *list = freeroms->search(atarijaguar, "NBA");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("NBA Jam TE (1996)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_atarilynx() {
    acll_t *list = freeroms->search(atarilynx, "Conners Tennis");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Jimmy Conners Tennis (1991)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_atarist() {
    acll_t *list = freeroms->search(atarist, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_c64() {
    acll_t *list = freeroms->search(c64, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_dreamcast() {
    acll_t *list = freeroms->search(dreamcast, "Dalmations To The Rescue");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("101 Dalmations To The Rescue", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_fba() {
    acll_t *list = freeroms->search(fba, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_fds() {
    acll_t *list = freeroms->search(fds, "Z-Gunda");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Z-Gundam", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gamegear() {
    acll_t *list = freeroms->search(gamegear, "Excellent Dizzy");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Excellent Dizzy", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gb() {
    acll_t *list = freeroms->search(gb, "Oide Rascal");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Oide Rascal (Japan)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gba() {
    acll_t *list = freeroms->search(gba, "Helsing");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Van Helsing", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gbc() {
    acll_t *list = freeroms->search(gbc, "Olympic Summer");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Olympic Summer Games", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gc() {
    acll_t *list = freeroms->search(gc, "Sorcerers Stone");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Harry Potter and the Sorcerers Stone", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_genesis() {
    acll_t *list = freeroms->search(genesis, "NBA Jam");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("NBA Jam Tournament Edition (32X)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_gw() {
    acll_t *list = freeroms->search(gw, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_love() {
    acll_t *list = freeroms->search(love, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_mame() {
    acll_t *list = freeroms->search(mame, "Quadro Quiz");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Quadro Quiz II", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_mastersystem() {
    acll_t *list = freeroms->search(mastersystem, "Out Run 3D");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Out Run 3D", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_megadrive() {
    acll_t *list = freeroms->search(megadrive, "NBA Jam");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("NBA Jam Tournament Edition (32X)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_msx() {
    acll_t *list = freeroms->search(msx, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_n64() {
    acll_t *list = freeroms->search(n64, "Mario Kart");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Mario Kart 64", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_nds() {
    acll_t *list = freeroms->search(nds, "Mario and Luigi Partners in Time Europe");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Mario and Luigi Partners in Time Europe", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_neogeo() {
    acll_t *list = freeroms->search(neogeo, "Infinity Cure");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Infinity Cure (J) [!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_nes() {
    acll_t *list = freeroms->search(nes, "Z-Gunda");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Z-Gundam", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_ngp() {
    acll_t *list = freeroms->search(ngp, "Wrestling Madness");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Wrestling Madness (Beta)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_ngpc() {
    acll_t *list = freeroms->search(ngpc, "Magical Drop Pocket Hack");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Magical Drop Pocket Hack", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_pc() {
    acll_t *list = freeroms->search(pc, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_pcengine() {
    acll_t *list = freeroms->search(pcengine, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_pcfx() {
    acll_t *list = freeroms->search(pcfx, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_ps2() {
    acll_t *list = freeroms->search(ps2, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_psp() {
    acll_t *list = freeroms->search(psp, "Qix");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Qix++ Japan", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_psx() {
    acll_t *list = freeroms->search(psx, "Panzer Front");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Panzer Front", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_saturn() {
    acll_t *list = freeroms->search(saturn, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_scummvm() {
    acll_t *list = freeroms->search(scummvm, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_sega32x() {
    acll_t *list = freeroms->search(sega32x, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_segacd() {
    acll_t *list = freeroms->search(segacd, "NBA Jam");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("NBA Jam Tournament Edition (32X)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_sg1000() {
    acll_t *list = freeroms->search(sg1000, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_snes() {
    acll_t *list = freeroms->search(snes, "Q-bert");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Q-bert 3", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_vectrex() {
    acll_t *list = freeroms->search(vectrex, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_videopac() {
    acll_t *list = freeroms->search(videopac, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_virtualboy() {
    acll_t *list = freeroms->search(virtualboy, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_wii() {
    acll_t *list = freeroms->search(wii, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_wiiu() {
    acll_t *list = freeroms->search(wiiu, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_wonderswan() {
    acll_t *list = freeroms->search(wonderswan, "Tetsuman");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Tetsuman (J) [M][!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_freeroms_wonderswancolor() {
    acll_t *list = freeroms->search(wonderswancolor, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_zxspectrum() {
    acll_t *list = freeroms->search(zxspectrum, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_freeroms_download() {
    acll_t *list = freeroms->search(amiga, "DAMAGE");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Damage", getResult(list)->title);


    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Damage.zip";
    testdata->title = "Damage";
    testdata->system = amiga;
    testdata->data = NULL;
    testdata->url = "https://www.freeroms.com/dl_roms/rom_download_tr.php?system=amiga&game_id=10579";

    freeroms->download(getResult(list), testDownloadCallback, testdata);

    free(testdata);

    result_freeList(list);
    return 0;
}

