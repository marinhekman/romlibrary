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

int test_engine_romsdownload_3do() {
    return run_test_inactive(threeDo);
}

int test_engine_romsdownload_amiga() {
    return run_test_active(amiga, "Bubble", "Bubble Bobble");
}

int test_engine_romsdownload_atari2600() {
    return run_test_active(atari2600, "Sabotage", "Sabotage (Ultravison)");
}

int test_engine_romsdownload_atari7800() {
    return run_test_active(atari7800, "Pac", "Ms. Pac-Man (1987) (Atari)");
}

int test_engine_romsdownload_atarijaguar() {
    return run_test_active(atarijaguar, "Raiden", "Raiden (1994)");
}

int test_engine_romsdownload_atarilynx() {
    return run_test_active(atarilynx, "Toki", "Toki (1990)");
}

int test_engine_romsdownload_atarist() {
    return run_test_active(atarist, "Rock Star", "Rock Star Ate My Hamster (Europe)");
}

int test_engine_romsdownload_c64() {
    return run_test_active(c64, "Mario", "Mariobros");
}

int test_engine_romsdownload_dreamcast() {
    return run_test_inactive(dreamcast);
}

int test_engine_romsdownload_fba() {
    return run_test_inactive(fba);
}

int test_engine_romsdownload_fds() {
    return run_test_active(fds, "Zelda", "Zelda No Densetsu - The Hyrule Fantasy (v1.1)");
}

int test_engine_romsdownload_gamegear() {
    return run_test_active(gamegear, "Mortal Kombat", "Mortal Kombat II");
}

int test_engine_romsdownload_gb() {
    return run_test_active(gb, "Mario", "Super Mario Land 4");
}

int test_engine_romsdownload_gba() {
    return run_test_active(gba, "Pokemon", "Pokemon White Version By MB Hacks (Blue Hack) GoombaV2.2");
}

int test_engine_romsdownload_gbc() {
    return run_test_active(gbc, "Zelda", "Legend Of Zelda, The - Link's Awakening DX (V1.2)");
}

int test_engine_romsdownload_gc() {
    return run_test_active(gc, "zelda", "Legend Of Zelda The The Wind Waker");
}

int test_engine_romsdownload_genesis() {
    return run_test_active(genesis, "Street", "Street Fighter 2 Special Champion Edition");
}

int test_engine_romsdownload_gw() {
    return run_test_inactive(gw);
}

int test_engine_romsdownload_love() {
    return run_test_inactive(love);
}

int test_engine_romsdownload_mame() {
    return run_test_active(mame, "64street", "64street");
}

int test_engine_romsdownload_mastersystem() {
    return run_test_active(mastersystem, "Bros", "Bonanza Bros");
}

int test_engine_romsdownload_megadrive() {
    return run_test_active(megadrive, "Special", "Street Fighter 2 Special Champion Edition");
}

int test_engine_romsdownload_msx() {
    return run_test_active(msx, "Dragon", "Dragon Quest 1");
}

int test_engine_romsdownload_n64() {
    return run_test_active(n64, "Mortal Kombat", "Mortal Kombat 4");
}

int test_engine_romsdownload_nds() {
    return run_test_active(nds, "Mario Kart", "Mario Kart DS");
}

int test_engine_romsdownload_neogeo() {
    return run_test_active(neogeo, "Captcomm", "Captcomm");
}

int test_engine_romsdownload_nes() {
    return run_test_active(nes, "Mario", "Super Mario Bros");
}

int test_engine_romsdownload_ngp() {
    return run_test_active(ngp, "King",
                           "King Of Fighters R-1 & Melon-chan No Seichou Nikki - Pocket Fighting Series (Demo)");
}

int test_engine_romsdownload_ngpc() {
    return run_test_active(ngpc, "Hedgehog", "Sonic The Hedgehog - Pocket Adventure (World)");
}

int test_engine_romsdownload_pc() {
    return run_test_inactive(pc);
}

int test_engine_romsdownload_pcengine() {
    return run_test_active(pcengine, "Street Fighter", "Street Fighter II' - Champion Edition Sounds");
}

int test_engine_romsdownload_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_romsdownload_ps2() {
    return run_test_active(ps2, "Racing", "Rumble Racing");
}

int test_engine_romsdownload_psp() {
    return run_test_active(psp, "Tekken", "Tekken 6");
}

int test_engine_romsdownload_psx() {
    return run_test_active(psx, "Crash Bandicoot", "Crash Bandicoot [SCUS-94900]");
}

int test_engine_romsdownload_saturn() {
    return run_test_inactive(saturn);
}

int test_engine_romsdownload_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_romsdownload_sega32x() {
    return run_test_active(sega32x, "Doom", "Doom");
}

int test_engine_romsdownload_segacd() {
    return run_test_active(segacd, "Street", "Street Fighter 2 Special Champion Edition");
}

int test_engine_romsdownload_sg1000() {
    return run_test_active(sg1000, "Runner", "Championship Lode Runner");
}

int test_engine_romsdownload_snes() {
    return run_test_active(snes, "Top Gear", "Top Gear");
}

int test_engine_romsdownload_vectrex() {
    return run_test_active(vectrex, "Coaster", "3D Crazy Coaster");
}

int test_engine_romsdownload_videopac() {
    return run_test_active(videopac, "Battle", "Air Battle (Europe)");
}

int test_engine_romsdownload_virtualboy() {
    return run_test_active(virtualboy, "Waterworld", "Waterworld");
}

int test_engine_romsdownload_wii() {
    return run_test_active(wii, "Party", "Mario Party 8");
}

int test_engine_romsdownload_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_romsdownload_wonderswan() {
    return run_test_active(wonderswan, "Digimon Tamers", "Digimon Tamers - Digimon Medley (j) [f1]");
}

int test_engine_romsdownload_wonderswancolor() {
    return run_test_inactive(wonderswancolor);
}

int test_engine_romsdownload_zxspectrum() {
    return run_test_active(zxspectrum, "Drinker", "Drinker, The (1986)(Suzy Soft)(sr)");
}

int test_engine_romsdownload_download() {
    acll_t *list = romsdownload->search(nes, "Mario");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Super Mario Bros 2");
    ASSERTSTR("Super Mario Bros 2", rl_getResult(list)->title);

    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Super Mario Bros 2.zip";
    testdata->title = "Super Mario Bros 2";
    testdata->system = nes;
    testdata->data = NULL;
    testdata->url = "http://185.232.52.56/romfiles/nintendo/s/super-mario-bros-2-japan.zip";

    romsdownload->download(rl_getResult(list), testDownloadCallback, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = romsdownload->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = romsdownload->search(system, "");
    ASSERTNULL(list);
    return 0;
}