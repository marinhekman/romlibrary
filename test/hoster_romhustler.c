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

int test_engine_romhustler_3do() {
    acll_t *list = romhustler->search(threeDo, "Scramble Cobra");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Scramble Cobra (1994)(Panasonic)(Eu)[CDD8990]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_amiga() {
    acll_t *list = romhustler->search(amiga, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_atari2600() {
    acll_t *list = romhustler->search(atari2600, "Sabotage");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sabotage (Ultravison)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_atari7800() {
    acll_t *list = romhustler->search(atari7800, "NTSC");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("NTSC Encryption Backdoor Test (2000) (PD)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_atarijaguar() {
    acll_t *list = romhustler->search(atarijaguar, "Ladybug");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Ladybug Demo (PD)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_atarilynx() {
    acll_t *list = romhustler->search(atarilynx, "Fighter");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Fighter V.2 Demo (2000) (PD)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_atarist() {
    acll_t *list = romhustler->search(atarist, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_c64() {
    acll_t *list = romhustler->search(c64, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_dreamcast() {
    acll_t *list = romhustler->search(dreamcast, "Zombie");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Zombie Revenge USA DC-KALISTO", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_fba() {
    acll_t *list = romhustler->search(fba, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_fds() {
    acll_t *list = romhustler->search(fds, "Contra");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Contra", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gamegear() {
    acll_t *list = romhustler->search(gamegear, "Panzer");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Panzer Dragoon Mini (J) [!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gb() {
    acll_t *list = romhustler->search(gb, "Mario");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Dr. Mario (V1.0) (JU) [!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gba() {
    acll_t *list = romhustler->search(gba, "Street");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Midnight Club - Street Racing (Europe) (En,Fr,De,Es,It)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gbc() {
    acll_t *list = romhustler->search(gbc, "Mario");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Dr. Mario (V1.0) (JU) [!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gc() {
    acll_t *list = romhustler->search(gc, "Street");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("FIFA Street (U)(OneUp)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_genesis() {
    acll_t *list = romhustler->search(genesis, "Sonic");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sonic 3D Blast", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_gw() {
    acll_t *list = romhustler->search(gw, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_love() {
    acll_t *list = romhustler->search(love, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_mame() {
    acll_t *list = romhustler->search(mame, "road");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Battle K-Road", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_mastersystem() {
    acll_t *list = romhustler->search(mastersystem, "Sonic");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sonic Blast (UE) [!]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_megadrive() {
    acll_t *list = romhustler->search(megadrive, "Sonic");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sonic 3D Blast", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_msx() {
    acll_t *list = romhustler->search(msx, "Gradius");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Gradius (1986) (Konami) (J)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_n64() {
    acll_t *list = romhustler->search(n64, "Mortal Kombat");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Mortal Kombat 4", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_nds() {
    acll_t *list = romhustler->search(nds, "Pokemon");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Pokemon - HeartGold (JP)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_neogeo() {
    acll_t *list = romhustler->search(neogeo, "Metal Slug");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Metal Slug", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_nes() {
    acll_t *list = romhustler->search(nes, "Mario");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Dr. Mario", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_ngp() {
    acll_t *list = romhustler->search(ngp, "Metal");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Metal Slug - 1st Mission (JUE)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_ngpc() {
    acll_t *list = romhustler->search(ngpc, "Metal");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Metal Slug - 1st Mission (JUE)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_pc() {
    acll_t *list = romhustler->search(pc, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_pcengine() {
    acll_t *list = romhustler->search(pcengine, "image");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Image Fight 2 - Operation Deepstriker (NTSC-J) [ICCD2002]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_pcfx() {
    acll_t *list = romhustler->search(pcfx, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_ps2() {
    acll_t *list = romhustler->search(ps2, "Grandia");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Grandia II (USA)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_psp() {
    acll_t *list = romhustler->search(psp, "mortal");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Mortal Kombat - Unchained (E)(M5)(pSyPSP)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_psx() {
    acll_t *list = romhustler->search(psx, "mortal");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Mortal Kombat - Special Forces [U] [SLUS-00824]", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_saturn() {
    acll_t *list = romhustler->search(saturn, "Sonic");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sonic 3D Blast (U)(Saturn)", getResult(list)->title);
    result_freeList(list);
    return 0;;
}

int test_engine_romhustler_scummvm() {
    acll_t *list = romhustler->search(scummvm, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_sega32x() {
    acll_t *list = romhustler->search(sega32x, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_segacd() {
    acll_t *list = romhustler->search(segacd, "Sonic");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Sonic CD (U)", getResult(list)->title);
    result_freeList(list);
    return 0;;
}

int test_engine_romhustler_sg1000() {
    acll_t *list = romhustler->search(sg1000, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_snes() {
    acll_t *list = romhustler->search(snes, "Mario");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Dr. Mario", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_vectrex() {
    acll_t *list = romhustler->search(vectrex, "Mine");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("3-D Mine Storm (1983)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_videopac() {
    acll_t *list = romhustler->search(videopac, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_virtualboy() {
    acll_t *list = romhustler->search(virtualboy, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_wii() {
    acll_t *list = romhustler->search(wii, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_wiiu() {
    acll_t *list = romhustler->search(wiiu, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_wonderswan() {
    acll_t *list = romhustler->search(wonderswan, "hunter");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Hunter X Hunter - Greed Island (J)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_wonderswancolor() {
    acll_t *list = romhustler->search(wonderswancolor, "hunter");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Hunter X Hunter - Greed Island (J)", getResult(list)->title);
    result_freeList(list);
    return 0;
}

int test_engine_romhustler_zxspectrum() {
    acll_t *list = romhustler->search(zxspectrum, "");
    ASSERTNULL(list);
    return 0;
}

int test_engine_romhustler_download() {
    acll_t *list = romhustler->search(nes, "Mario");
    ASSERTNOTNULL(list);
    list = result_sort(list);
    ASSERTSTR("Dr. Mario", getResult(list)->title);


    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Dr. Mario.zip";
    testdata->title = "Dr. Mario";
    testdata->system = nes;
    testdata->data = NULL;
    testdata->url = "https://romhustler.org/rom/nes/dr-mario-1";

    freeroms->download(getResult(list), testDownloadCallback, testdata);

    free(testdata);

    result_freeList(list);
    return 0;
}