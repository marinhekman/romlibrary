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

uint8_t
testDownloadCallbackRomsEmulator(void *appData, rl_system *system, char *title, char *url, char *data, char *filename,
                                 chttp_method method);

int test_engine_romsemulator_3do() {
    return run_test_inactive(threeDo);
}

int test_engine_romsemulator_amiga() {
    return run_test_active(amiga, "DAMAGE", "Damage – The Sadistic Butchering Of Humanity_Disk1");
}

int test_engine_romsemulator_atari2600() {
    return run_test_active(atari2600, "PENGO", "Pengo (1984) (Atari)");
}

int test_engine_romsemulator_atari7800() {
    return run_test_active(atari7800, "toppler", "Tower Toppler (1988) (Atari)");
}

int test_engine_romsemulator_atarijaguar() {
    return run_test_active(atarijaguar, "NBA", "Ruiner Pinball (1995)");
}

int test_engine_romsemulator_atarilynx() {
    return run_test_active(atarilynx, "Skweek", "Super Skweek (1991)");
}

int test_engine_romsemulator_atarist() {
    return run_test_active(atarist, "Balance of Power", "Balance Of Power – The 1990 Edition (Europe)");
}

int test_engine_romsemulator_c64() {
    return run_test_active(c64, "Neuromancer", "Neuromancer");
}

int test_engine_romsemulator_dreamcast() {
    return run_test_inactive(dreamcast);
}

int test_engine_romsemulator_fba() {
    return run_test_inactive(fba);
}

int test_engine_romsemulator_fds() {
    return run_test_active(fds, "Mario", "Super Mario World");
}

int test_engine_romsemulator_gamegear() {
    return run_test_active(gamegear, "Excellent Dizzy", "Excellent Dizzy Collection, The");
}

int test_engine_romsemulator_gb() {
    return run_test_active(gb, "WWF", "WWF King Of The Ring");
}

int test_engine_romsemulator_gba() {
    return run_test_active(gba, "Golden", "Golden Sun – The Lost Age");
}

int test_engine_romsemulator_gbc() {
    return run_test_active(gbc, "Beatmania", "Beatmania GB Gotcha Mix 2");
}

int test_engine_romsemulator_gc() {
    return run_test_active(gc, "Mario", "Super Mario Sunshine");
}

int test_engine_romsemulator_genesis() {
    return run_test_active(genesis, "NBA Jam", "NBA Jam Tournament Edition (JUE) (REV 00)");
}

int test_engine_romsemulator_gw() {
    return run_test_inactive(gw);
}

int test_engine_romsemulator_love() {
    return run_test_inactive(love);
}

int test_engine_romsemulator_mame() {
    return run_test_active(mame, "Tron", "Tron");
}

int test_engine_romsemulator_mastersystem() {
    return run_test_active(mastersystem, "Out Run 3D", "OutRun 3D");
}

int test_engine_romsemulator_megadrive() {
    return run_test_active(megadrive, "NBA Jam", "NBA Jam Tournament Edition (JUE) (REV 00)");
}

int test_engine_romsemulator_msx() {
    return run_test_active(msx, "Galious", "Maze Of Galious");
}

int test_engine_romsemulator_n64() {
    return run_test_active(n64, "Mario Kart", "Mario Kart 64 (V1.1)");
}

int test_engine_romsemulator_nds() {
    return run_test_active(nds, "Super Mario 64 DS", "Super Mario 64 DS");
}

int test_engine_romsemulator_neogeo() {
    return run_test_active(neogeo, "Turfmast", "Turfmast");
}

int test_engine_romsemulator_nes() {
    return run_test_active(nes, "Mario", "Super Mario World");
}

int test_engine_romsemulator_ngp() {
    return run_test_active(ngp, "Baseball Stars", "Baseball Stars (Japan, Europe) (En,Ja)");
}

int test_engine_romsemulator_ngpc() {
    return run_test_active(ngpc, "Biomotor Unitron", "Biomotor Unitron");
}

int test_engine_romsemulator_pc() {
    return run_test_inactive(pc);
}

int test_engine_romsemulator_pcengine() {
    return run_test_active(pcengine, "Rastan", "Rastan Saga II [b2]");
}

int test_engine_romsemulator_pcfx() {
    return run_test_inactive(pcfx);
}

int test_engine_romsemulator_ps2() {
    return run_test_inactive(ps2);
}

int test_engine_romsemulator_psp() {
    return run_test_inactive(psp);
}

int test_engine_romsemulator_psx() {
    return run_test_active(psx, "Panzer Front", "Panzer Front [SLUS-01399]");
}

int test_engine_romsemulator_saturn() {
    return run_test_inactive(saturn);
}

int test_engine_romsemulator_scummvm() {
    return run_test_inactive(scummvm);
}

int test_engine_romsemulator_sega32x() {
    return run_test_active(sega32x, "Zaxxon", "Zaxxon’s Motherbase 2000");
}

int test_engine_romsemulator_segacd() {
    return run_test_active(segacd, "NBA Jam", "Blockbuster Competition 2 – NBA Jam & Judge Dredd (JUE)");
}

int test_engine_romsemulator_sg1000() {
    return run_test_active(sg1000, "Home", "Home Basic (SC-3000)");
}

int test_engine_romsemulator_snes() {
    return run_test_active(snes, "Q-bert", "Q-bert 3");
}

int test_engine_romsemulator_vectrex() {
    return run_test_active(vectrex, "Scramble", "Scramble (USA, Europe)");
}

int test_engine_romsemulator_videopac() {
    return run_test_active(videopac, "Brandt", "[BIOS] Brandt Jopac (France)");
}

int test_engine_romsemulator_virtualboy() {
    return run_test_active(virtualboy, "Red Alarm", "Red Alarm");
}

int test_engine_romsemulator_wii() {
    return run_test_inactive(wii);
}

int test_engine_romsemulator_wiiu() {
    return run_test_inactive(wiiu);
}

int test_engine_romsemulator_wonderswan() {
    return run_test_active(wonderswan, "Blue Wing Blitz", "Blue Wing Blitz [M].ws");
}

int test_engine_romsemulator_wonderswancolor() {
    return run_test_inactive(wonderswancolor);
}

int test_engine_romsemulator_zxspectrum() {
    return run_test_active(zxspectrum, "Tank",
                           "Battle-Tank Simulator (1989)(Zeppelin Games)[master Tape][aka 3D Tank Duel]");
}

int test_engine_romsemulator_download() {
    acll_t *list = romsemulator->search(amiga, "DAMAGE");
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, "Damage – The Sadistic Butchering Of Humanity_Disk1");
    ASSERTSTR("Damage – The Sadistic Butchering Of Humanity_Disk1", rl_getResult(list)->title);

    test_downloaddata_t *testdata = calloc(1, sizeof(test_downloaddata_t));
    testdata->method = POST;
    testdata->filename = "Damage – The Sadistic Butchering Of Humanity_Disk1.zip";
    testdata->title = "Damage – The Sadistic Butchering Of Humanity_Disk1";
    testdata->system = amiga;
    testdata->data = "action=roms_download_file&pid=NTE2MDI&roms_download_file_nonce_field=7f467dcd63&_wp_http_referer=/roms/damage-the-sadistic-butchering-of-humanity_disk1/?pid=NTE2MDI";
    testdata->url = "https://romsemulator.net/roms/damage-the-sadistic-butchering-of-humanity_disk1/?pid=NTE2MDI";

    romsemulator->download(rl_getResult(list), testDownloadCallbackRomsEmulator, testdata);

    free(testdata);

    rl_results_free(list);
    return 0;
}

static int run_test_active(rl_system *system, char *searchString, char *includedTitle) {
    acll_t *list = romsemulator->search(system, searchString);
    ASSERTNOTNULL(list);
    list = acll_find(list, resultFilter, includedTitle);
    ASSERTSTR(includedTitle, rl_getResult(list)->title);
    rl_results_free(list);
    return 0;
}

static int run_test_inactive(rl_system *system) {
    acll_t *list = romsemulator->search(system, "");
    ASSERTNULL(list);
    return 0;
}

uint8_t
testDownloadCallbackRomsEmulator(void *appData, rl_system *system, char *title, char *url, char *data, char *filename,
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

    if (input->url == NULL) {
        ASSERTNULL(url);
    } else {
        ASSERTNOTNULL(url);
        ASSERTSTR(input->url, url);
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