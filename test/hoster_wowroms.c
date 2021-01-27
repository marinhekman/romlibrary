/*
 * Copyright 2021 Maximilian Voss (maximilian@voss.rocks)
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

int test_engine_wowroms_3do() {
    return run_test_inactive(threeDo);
}

int test_engine_wowroms_amiga() {
    return run_test_active(amiga, "zork", "ZORK ZERO : THE REVENGE OF MEG");
}

int test_engine_wowroms_atari2600() {
    return run_test_active(atari2600, "attack", "ASTRO ATTACK [EUROPE]");
}

int test_engine_wowroms_atari7800() {
    return run_test_active(atari7800, "GHOST MANOR", "Ghost Manor");
}

int test_engine_wowroms_atarijaguar() {
    return run_test_active(atarijaguar, "Cannon", "CANNON FODDER");
}

int test_engine_wowroms_atarilynx() {
    return run_test_active(atarilynx, "Soccer", "EUROPEAN SOCCER CHALLENGE [USA");
}

int test_engine_wowroms_atarist() {
    return run_test_active(atarist, "Gobliiins", "GOBLIIINS [ST]");
}

int test_engine_wowroms_c64() {
    return run_test_active(c64, "Sweeper", "Star Sweeper");
}


int test_engine_wowroms_dreamcast() {
    return run_test_inactive(dreamcast);
}

int test_engine_wowroms_fba() {
    return run_test_inactive(fba);
}

int test_engine_wowroms_fds() {
    return run_test_active(fds, "Control", "BISHOUJO CONTROL [JAPAN] (UNL)");
}

int test_engine_wowroms_gamegear() {
    return run_test_active(gamegear, "Berlin", "BERLIN NO KABE [JAPAN]");
}

int test_engine_wowroms_gb() {
    return run_test_active(gb, "Batman", "Batman Forever (Japan)");
}

int test_engine_wowroms_gba() {
    return run_test_active(gba, "escape", "Escape from the Dark Prison");
}

int test_engine_wowroms_gbc() {
    return run_test_active(gbc, "Animorphs", "Animorphs [USA]");
}

int test_engine_wowroms_gc() {
    return run_test_inactive(gc);
}

int test_engine_wowroms_genesis() {
    return run_test_active(genesis, "Agassi", "Andre Agassi Tennis [Europe]");
}

int test_engine_wowroms_gw() {
    return run_test_inactive(gw);
}

int test_engine_wowroms_love() {
    return run_test_inactive(love);
}

int test_engine_wowroms_mame() {
    return run_test_active(mame, "amazing", "AMAZING MAZE");
}

int test_engine_wowroms_mastersystem() {
    return run_test_active(mastersystem, "Astro", "ASTRO FLASH [JAPAN]");
}

int test_engine_wowroms_megadrive() {
    return run_test_active(megadrive, "aero", "Aero the Acro-Bat [USA]");
}

int test_engine_wowroms_msx() {
    return run_test_inactive(msx);
}

int test_engine_wowroms_n64() {
    return run_test_active(n64, "Bio", "Bio F.R.E.A.K.S. [USA]");
}

int test_engine_wowroms_nds() {
    return run_test_active(nds, "gold", "Level5 Premium - Gold [Japan]");
}

int test_engine_wowroms_neogeo() {
    return run_test_active(neogeo, "wolves", "GAROU - MARK OF THE WOLVES");
}

int test_engine_wowroms_nes() {
    return run_test_active(nes, "lolo", "Adventures of Lolo 2 [Japan]");
}

int test_engine_wowroms_ngp() {
    return run_test_active(ngp, "tennis", "POCKET TENNIS - POCKET SPORTS");
}

int test_engine_wowroms_ngpc() {
    return run_test_active(ngpc, "king of fighters", "KING OF FIGHTERS - R-2 (DEMO)");
}

int test_engine_wowroms_pc() {
    return run_test_inactive(pc);
}

int test_engine_wowroms_pcengine() {
    return run_test_active(pcengine, "cadash", "CADASH [JAPAN]");
}

int test_engine_wowroms_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_wowroms_ps2() {
    return run_test_active(ps2, "metallica", "GUITAR HERO : METALLICA");
}

int test_engine_wowroms_psp() {
    return run_test_active(psp, "jam", "4×4 Jam [USA]");
}

int test_engine_wowroms_psx() {
    return run_test_active(psx, "arc", "Arc the Lad III [USA]");
}

int test_engine_wowroms_saturn() {
    return run_test_inactive(saturn);
}

int test_engine_wowroms_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_wowroms_sega32x() {
    return run_test_active(sega32x, "GREAT HOLES", "36 GREAT HOLES [USA]");
}

int test_engine_wowroms_segacd() {
    return run_test_active(segacd, "rugby", "Australian Rugby League [Europ");
}

int test_engine_wowroms_sg1000() {
    return run_test_active(sg1000, "HISSHUU", "CHUUGAKU HISSHUU EISAKUBUN (CH");
}

int test_engine_wowroms_snes() {
    return run_test_active(snes, "aero", "Aero the Acro-Bat [Europe]");
}

int test_engine_wowroms_vectrex() {
    return run_test_inactive(vectrex);
}

int test_engine_wowroms_videopac() {
    return run_test_inactive(videopac);
}

int test_engine_wowroms_virtualboy() {
    return run_test_active(virtualboy, "water", "WATERWORLD [USA]");
}

int test_engine_wowroms_wii() {
    return run_test_inactive(wii);
}

int test_engine_wowroms_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_wowroms_wonderswan() {
    return run_test_active(wonderswan, "Millennium", "Sennou Millennium [Japan]");
}

int test_engine_wowroms_wonderswancolor() {
    return run_test_active(wonderswancolor, "tetris", "Tetris [Japan]");
}

int test_engine_wowroms_zxspectrum() {
    return run_test_active(zxspectrum, "quest", "QUEST FOR ETERNITY");
}

int test_engine_wowroms_download() {
    acll_t *list = wowroms->search(wonderswancolor, "tetris");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Tetris [Japan]");
    ASSERTSTR("Tetris [Japan]", rl_getResult(list)->title);


    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Tetris [Japan].zip";
    testdata->title = "Tetris [Japan]";
    testdata->system = wonderswancolor;
    testdata->data = NULL;
    testdata->url = "https://download.wowroms.com/d/roms/g/1cAKtBm3o0NLhCJpaIhz/k1/26e772ec61211c4/k2/247b674b2b8516c";

    wowroms->download(rl_getResult(list), testDownloadCallback, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = wowroms->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = wowroms->search(system, "");
    ASSERTNULL(list);
    return 0;
}
