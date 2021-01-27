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

int test_engine_romhustler_3do() {
    return run_test_active(threeDo, "Scramble Cobra", "Scramble Cobra (1994)(Panasonic)(Eu)[CDD8990]");
}

int test_engine_romhustler_amiga() {
    return run_test_inactive(amiga);
}

int test_engine_romhustler_atari2600() {
    return run_test_active(atari2600, "Sabotage", "Sabotage (Ultravison)");
}

int test_engine_romhustler_atari7800() {
    return run_test_active(atari7800, "NTSC", "NTSC Encryption Backdoor Test (2000) (PD)");
}

int test_engine_romhustler_atarijaguar() {
    return run_test_active(atarijaguar, "Ladybug", "Ladybug Demo (PD)");
}

int test_engine_romhustler_atarilynx() {
    return run_test_active(atarilynx, "Fighter", "Fighter V.2 Demo (2000) (PD)");
}

int test_engine_romhustler_atarist() {
    return run_test_inactive(atarist);
}

int test_engine_romhustler_c64() {
    return run_test_inactive(c64);
}

int test_engine_romhustler_dreamcast() {
    return run_test_active(dreamcast, "Zombie", "Zombie Revenge USA DC-KALISTO");
}

int test_engine_romhustler_fba() {
    return run_test_inactive(fba);
}

int test_engine_romhustler_fds() {
    return run_test_active(fds, "Contra", "Contra");
}

int test_engine_romhustler_gamegear() {
    return run_test_active(gamegear, "Panzer", "Panzer Dragoon Mini (J) [!]");
}

int test_engine_romhustler_gb() {
    return run_test_active(gb, "Mario", "Dr. Mario (V1.0) (JU) [!]");
}

int test_engine_romhustler_gba() {
    return run_test_active(gba, "Street", "Midnight Club - Street Racing (Europe) (En,Fr,De,Es,It)");
}

int test_engine_romhustler_gbc() {
    return run_test_active(gbc, "Mario", "Dr. Mario (V1.0) (JU) [!]");
}

int test_engine_romhustler_gc() {
    return run_test_active(gc, "Street", "FIFA Street (U)(OneUp)");
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
    return run_test_active(mastersystem, "Sonic", "Sonic Blast (UE) [!]");
}

int test_engine_romhustler_megadrive() {
    return run_test_active(megadrive, "Sonic", "Sonic 3D Blast");
}

int test_engine_romhustler_msx() {
    return run_test_active(msx, "Gradius", "Gradius (1986) (Konami) (J)");
}

int test_engine_romhustler_n64() {
    return run_test_active(n64, "Mortal Kombat", "Mortal Kombat 4");
}

int test_engine_romhustler_nds() {
    return run_test_active(nds, "Pokemon", "Pokemon - HeartGold (JP)");
}

int test_engine_romhustler_neogeo() {
    return run_test_active(neogeo, "Metal Slug", "Metal Slug");
}

int test_engine_romhustler_nes() {
    return run_test_active(nes, "Mario", "Dr. Mario");
}

int test_engine_romhustler_ngp() {
    return run_test_active(ngp, "Metal", "Metal Slug - 1st Mission (JUE)");
}

int test_engine_romhustler_ngpc() {
    return run_test_active(ngpc, "Metal", "Metal Slug - 1st Mission (JUE)");
}

int test_engine_romhustler_pc() {
    return run_test_inactive(pc);
}

int test_engine_romhustler_pcengine() {
    return run_test_active(pcengine, "image", "Image Fight 2 - Operation Deepstriker (NTSC-J) [ICCD2002]");
}

int test_engine_romhustler_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_romhustler_ps2() {
    return run_test_active(ps2, "Grandia", "Grandia II (USA)");
}

int test_engine_romhustler_psp() {
    return run_test_active(psp, "mortal", "Mortal Kombat - Unchained (E)(M5)(pSyPSP)");
}

int test_engine_romhustler_psx() {
    return run_test_active(psx, "mortal", "Mortal Kombat - Special Forces [U] [SLUS-00824]");
}

int test_engine_romhustler_saturn() {
    return run_test_active(saturn, "Sonic", "Sonic 3D Blast (U)(Saturn)");
}

int test_engine_romhustler_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_romhustler_sega32x() {
    return run_test_inactive(sega32x);
}

int test_engine_romhustler_segacd() {
    return run_test_active(segacd, "Sonic", "Sonic CD (U)");
}

int test_engine_romhustler_sg1000() {
    return run_test_inactive(sg1000);
}

int test_engine_romhustler_snes() {
    return run_test_active(snes, "Mario", "Dr. Mario");
}

int test_engine_romhustler_vectrex() {
    return run_test_active(vectrex, "Mine", "3-D Mine Storm (1983)");
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
    return run_test_active(wonderswan, "hunter", "Hunter X Hunter - Greed Island (J)");
}

int test_engine_romhustler_wonderswancolor() {
    return run_test_active(wonderswancolor, "hunter", "Hunter X Hunter - Greed Island (J)");
}

int test_engine_romhustler_zxspectrum() {
    return run_test_inactive(zxspectrum);
}

int test_engine_romhustler_download() {
    acll_t *list = romhustler->search(nes, "Mario");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Dr. Mario");
    ASSERTSTR("Dr. Mario", rl_getResult(list)->title);

    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Dr. Mario.zip";
    testdata->title = "Dr. Mario";
    testdata->system = nes;
    testdata->data = NULL;
    testdata->url = "https://romhustler.org/rom/nes/dr-mario-1";

    freeroms->download(rl_getResult(list), testDownloadCallback, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = romhustler->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = romhustler->search(system, "");
    ASSERTNULL(list);
    return 0;
}