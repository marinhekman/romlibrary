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

int test_engine_romsmania_3do() {
    return run_test_inactive(threeDo);
}

int test_engine_romsmania_amiga() {
    return run_test_active(amiga, "DAMAGE", "Damage - The Sadistic Butchering Of Humanity_Disk1");
}

int test_engine_romsmania_atari2600() {
    return run_test_active(atari2600, "PENGO", "Pengo (1984) (Atari)");
}

int test_engine_romsmania_atari7800() {
    return run_test_active(atari7800, "MARIO", "Mario Brothers (1988) (Atari)");
}

int test_engine_romsmania_atarijaguar() {
    return run_test_active(atarijaguar, "NBA", "NBA Jam TE (1996)");
}

int test_engine_romsmania_atarilynx() {
    return run_test_active(atarilynx, "Pac", "Pac-Land (1991)");
}

int test_engine_romsmania_atarist() {
    return run_test_active(atarist, "War", "War In Middle Earth (Europe)");
}

int test_engine_romsmania_c64() {
    return run_test_active(c64, "Deliverance.Hewson", "Deliverance.Hewson.+4-Light");
}

int test_engine_romsmania_dreamcast() {
    return run_test_active(dreamcast, "Blue Stinger", "Blue Stinger");
}

int test_engine_romsmania_fba() {
    return run_test_inactive(fba);
}

int test_engine_romsmania_fds() {
    return run_test_active(fds, "72", "72-in-1 [a1]");
}

int test_engine_romsmania_gamegear() {
    return run_test_active(gamegear, "aladdin", "Aladdin");
}

int test_engine_romsmania_gb() {
    return run_test_active(gb, "Amida", "Amida");
}

int test_engine_romsmania_gba() {
    return run_test_active(gba, "ace combat", "Ace Combat Advance GBA");
}

int test_engine_romsmania_gbc() {
    return run_test_active(gbc, "Buzz", "Buzz Lightyear Of Star Command");
}

int test_engine_romsmania_gc() {
    return run_test_active(gc, "007", "007 Todo O Nada");
}

int test_engine_romsmania_genesis() {
    return run_test_active(genesis, "Art", "Art Alive!");
}

int test_engine_romsmania_gw() {
    return run_test_inactive(gw);
}

int test_engine_romsmania_love() {
    return run_test_inactive(love);
}

int test_engine_romsmania_mame() {
    return run_test_active(mame, "ajax", "Ajax");
}

int test_engine_romsmania_mastersystem() {
    return run_test_active(mastersystem, "Sonic", "Sonic Chaos");
}

int test_engine_romsmania_megadrive() {
    return run_test_active(megadrive, "after", "After Burner II");
}

int test_engine_romsmania_msx() {
    return run_test_active(msx, "Balance", "Balance");
}

int test_engine_romsmania_n64() {
    return run_test_active(n64, "Dual Heroes", "Dual Heroes");
}

int test_engine_romsmania_nds() {
    return run_test_active(nds, "2550", "2550 - My Pet Hotel 2");
}

int test_engine_romsmania_neogeo() {
    return run_test_active(neogeo, "Ddsom", "Ddsom");
}

int test_engine_romsmania_nes() {
    return run_test_active(nes, "Alice Cooper", "Alice Cooper (SMB1 Hack) (Older)");
}

int test_engine_romsmania_ngp() {
    return run_test_active(ngp, "Samurai", "Samurai Shodown! - Pocket Fighting Series (Japan, Europe) (En,Ja)");
}

int test_engine_romsmania_ngpc() {
    return run_test_active(ngpc, "Metal Slug", "Metal Slug - 2nd Mission (World) (En,Ja) (Demo)");
}

int test_engine_romsmania_pc() {
    return run_test_inactive(pc);
}

int test_engine_romsmania_pcengine() {
    return run_test_active(pcengine, "battle", "Battle Lode Runner [b1]");
}

int test_engine_romsmania_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_romsmania_ps2() {
    return run_test_active(ps2, "Spider-Man", "Spider-Man 3");
}

int test_engine_romsmania_psp() {
    return run_test_active(psp, "Arcana", "Arcana Famiglia - Festa Regalo");
}

int test_engine_romsmania_psx() {
    return run_test_active(psx, "Army", "Army Men - World War [SLUS-01079]");
}

int test_engine_romsmania_saturn() {
    return run_test_inactive(saturn);
}

int test_engine_romsmania_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_romsmania_sega32x() {
    return run_test_active(sega32x, "Romance", "Romance Of The Three Kingdoms 4");
}

int test_engine_romsmania_segacd() {
    return run_test_active(segacd, "Bass Masters", "Bass Masters Classics (4)");
}

int test_engine_romsmania_sg1000() {
    return run_test_active(sg1000, "Yamato", "Yamato (Japan, Europe)");
}

int test_engine_romsmania_snes() {
    return run_test_active(snes, "alien", "Alien Vs. Predator");
}

int test_engine_romsmania_vectrex() {
    return run_test_active(vectrex, "web", "Web Warp (1983)");
}

int test_engine_romsmania_videopac() {
    return run_test_active(videopac, "Tresor", "Tresor Englouti, Le (France)");
}

int test_engine_romsmania_virtualboy() {
    return run_test_active(virtualboy, "Virtual", "Virtual Pro Yakyuu '95");
}

int test_engine_romsmania_wii() {
    return run_test_active(wii, "Boom Blox", "Boom Blox - Bash Party");
}

int test_engine_romsmania_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_romsmania_wonderswan() {
    return run_test_active(wonderswan, "Final Fantasy", "Final Fantasy (j)");
}

int test_engine_romsmania_wonderswancolor() {
    return run_test_inactive(wonderswancolor);
}

int test_engine_romsmania_zxspectrum() {
    return run_test_active(zxspectrum, "rider", "Rider (1984)(Virgin Games)[a][16K]");
}

int test_engine_romsmania_download() {
    acll_t *list = romsmania->search(wonderswan, "Final Fantasy");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Final Fantasy (j)");
    ASSERTSTR("Final Fantasy (j)", rl_getResult(list)->title);

    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = GET;
    testdata->filename = "Final Fantasy (j).zip";
    testdata->title = "Final Fantasy (j)";
    testdata->system = wonderswan;
    testdata->data = NULL;
    testdata->url = "https://s2roms.cc/s3roms/WonderSwan/final%20fantasy%20%28j%29%20%5B%21%5D.wsc";

    romsmania->download(rl_getResult(list), testDownloadCallback, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = romsmania->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = romsmania->search(system, "");
    ASSERTNULL(list);
    return 0;
}
