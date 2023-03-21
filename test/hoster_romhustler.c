/*
 * Copyright 2020 - 2021 Maximilian Voss (maximilian@voss.rocks)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"){ return 0; }
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

uint8_t testDownloadCallback_romhustler(void *appData, struct rl_system_s *system, char *title, char *url,
                                        struct curl_slist *headers,
                                        char *data,
                                        char *filename,
                                        chttp_method method) {
    test_downloaddata_t *input = appData;

    ASSERTNOTNULL(input);

    if (input->system == NULL) {
        ASSERTNULL(system);
    } else {
        ASSERTNOTNULL(system);
        ASSERTSTR(input->system->name, system->name);
    }

    if (input->title == NULL) {
        ASSERTNULL(title);
    } else {
        ASSERTNOTNULL(title);
        ASSERTSTR(input->title, title);
    }

    ASSERTNOTNULL(url);

    if (input->data == NULL) {
        ASSERTNULL(data);
    } else {
        ASSERTNOTNULL(data);
        ASSERTSTR(input->data, data);
    }

    if (input->filename == NULL) {
        ASSERTNULL(filename);
    } else {
        ASSERTNOTNULL(filename);
        ASSERTSTR(input->filename, filename);
    }

    ASSERTINT(input->method, method);
    return 0;
}

int test_engine_romhustler_3do() {
    return run_test_active(threeDo, "Scramble Cobra", "Scramble Cobra");
}

int test_engine_romhustler_amiga() {
    return run_test_inactive(amiga);
}

int test_engine_romhustler_atari2600() {
    return run_test_active(atari2600, "Sabotage", "Sabotage");
}

int test_engine_romhustler_atari7800() {
    return run_test_active(atari7800, "NTSC", "NTSC Encryption Backdoor Test");
}

int test_engine_romhustler_atarijaguar() {
    return run_test_active(atarijaguar, "Ladybug", "Ladybug Demo");
}

int test_engine_romhustler_atarilynx() {
    return run_test_active(atarilynx, "Fighter", "Pit Fighter - The Ultimate Competition");
}

int test_engine_romhustler_atarist() {
    return run_test_inactive(atarist);
}

int test_engine_romhustler_c64() {
    return run_test_inactive(c64);
}

int test_engine_romhustler_dreamcast() {
    return run_test_active(dreamcast, "Zombie", "Zombie Revenge");
}

int test_engine_romhustler_fba() {
    return run_test_inactive(fba);
}

int test_engine_romhustler_fds() {
    return run_test_active(fds, "Contra", "Contra");
}

int test_engine_romhustler_gamegear() {
    return run_test_active(gamegear, "Panzer", "Panzer Dragoon Mini [!]");
}

int test_engine_romhustler_gb() {
    return run_test_active(gb, "Mario", "Super Mario Quest");
}

int test_engine_romhustler_gba() {
    return run_test_active(gba, "Street", "Midnight Club - Street Racing");
}

int test_engine_romhustler_gbc() {
    return run_test_active(gbc, "Mario", "Super Mario Quest");
}

int test_engine_romhustler_gc() {
    return run_test_active(gc, "Digimon", "Digimon Rumble Arena 2");
}

int test_engine_romhustler_genesis() {
    return run_test_active(genesis, "Sonic", "Sonic 3D Blast");
}

int test_engine_romhustler_gw() {
    return run_test_inactive(gw);
}

int test_engine_romhustler_love() {
    return run_test_inactive(love);
}

int test_engine_romhustler_mame() {
    return run_test_active(mame, "road", "Battle K-Road");
}

int test_engine_romhustler_mastersystem() {
    return run_test_active(mastersystem, "Sonic", "Sonic Blast [!]");
}

int test_engine_romhustler_megadrive() {
    return run_test_active(megadrive, "Sonic", "Sonic 3D Blast");
}

int test_engine_romhustler_msx() {
    return run_test_active(msx, "Gradius", "Gradius");
}

int test_engine_romhustler_n64() {
    return run_test_active(n64, "Mortal Kombat", "Mortal Kombat 4");
}

int test_engine_romhustler_nds() {
    return run_test_active(nds, "Yu-Gi-Oh!", "Yu-Gi-Oh! 5D's - World Championship 2011 - Over the Nexus");
}

int test_engine_romhustler_neogeo() {
    return run_test_active(neogeo, "Metal Slug X", "Metal Slug X");
}

int test_engine_romhustler_nes() {
    return run_test_active(nes, "BIOS", "Famicom Disk System BIOS");
}

int test_engine_romhustler_ngp() {
    return run_test_active(ngp, "Metal", "Metal Slug - 1st Mission");
}

int test_engine_romhustler_ngpc() {
    return run_test_active(ngpc, "Metal", "Metal Slug [!]");
}

int test_engine_romhustler_pc() {
    return run_test_inactive(pc);
}

int test_engine_romhustler_pcengine() {
    return run_test_active(pcengine, "image", "Image Fight 2 - Operation Deepstriker");
}

int test_engine_romhustler_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_romhustler_ps2() {
    return run_test_inactive(ps2);
}

int test_engine_romhustler_psp() {
    return run_test_active(psp, "mortal", "Mortal Kombat - Unchained");
}

int test_engine_romhustler_psx() {
    return run_test_active(psx, "mortal", "Mortal Kombat - Special Forces");
}

int test_engine_romhustler_saturn() {
    return run_test_active(saturn, "Sonic", "Sonic 3D Blast");
}

int test_engine_romhustler_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_romhustler_sega32x() {
    return run_test_inactive(sega32x);
}

int test_engine_romhustler_segacd() {
    return run_test_active(segacd, "Sonic", "Sonic CD");
}

int test_engine_romhustler_sg1000() {
    return run_test_inactive(sg1000);
}

int test_engine_romhustler_snes() {
    return run_test_active(snes, "Final Fantasy", "Final Fantasy V");
}

int test_engine_romhustler_vectrex() {
    return run_test_inactive(vectrex);
}

int test_engine_romhustler_videopac() {
    return run_test_inactive(videopac);
}

int test_engine_romhustler_virtualboy() {
    return run_test_inactive(virtualboy);
}

int test_engine_romhustler_wii() {
    return run_test_inactive(wii);
}

int test_engine_romhustler_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_romhustler_wonderswan() {
    return run_test_active(wonderswan, "hunter", "Hunter X Hunter - Greed Island");
}

int test_engine_romhustler_wonderswancolor() {
    return run_test_active(wonderswancolor, "hunter", "Hunter X Hunter - Greed Island");
}

int test_engine_romhustler_zxspectrum() {
    return run_test_inactive(zxspectrum);
}

int test_engine_romhustler_download() {
    acll_t *list = romhustler->search(atarijaguar, "Ladybug");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Ladybug Demo");
    ASSERTSTR("Ladybug Demo", rl_getResult(list)->title);

    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Ladybug Demo (PD).rar";
    testdata->title = "Ladybug Demo";
    testdata->system = atarijaguar;
    testdata->data = NULL;
    testdata->url = "https://dl.romhustler.org/files/guest/eyJpdiI6IkFKQm1JZ0RiZEJQMFRsZnlFN2lKNXc9PSIsInZhbHVlIjoibWVocXE0cFFJWUtGNEIwdzAzMVRuYXJJTXhBQ0JLNlAxeStXWDJSdDBaRldGVktONlhLd2NPNDUwK3JPSktDcCIsIm1hYyI6IjVjYTcxMDEyM2ZjMzliYTYxMzg3ODI1Zjc0YWNiZTQzMGY3YzMxMzBmNmI4ZDA5YWMyZTRjMTMzMWVjNGUzZjciLCJ0YWciOiIifQ==/";

    romhustler->download(rl_getResult(list), testDownloadCallback_romhustler, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = romhustler->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTNOTNULL(list);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = romhustler->search(system, "");
    ASSERTNULL(list);
    return 0;
}