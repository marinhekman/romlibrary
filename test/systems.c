//
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

#include "systems.h"

acll_t *systems = NULL;

void testsystems_init() {
    systems = loadSystems();

    gb = getSystem(systems, "Game Boy");
    gbc = getSystem(systems, "Game Boy Color");
    gba = getSystem(systems, "Game Boy Advance");
    nes = getSystem(systems, "Nintendo Entertainment System");
    snes = getSystem(systems, "Super Nintendo Entertainment System");
    gc = getSystem(systems, "Nintendo GameCube");
    nds = getSystem(systems, "Nintendo DS");
    n64 = getSystem(systems, "Nintendo 64");
    wii = getSystem(systems, "Nintendo Wii");
    wiiu = getSystem(systems, "Nintendo Wii U");
    gw = getSystem(systems, "Game and Watch");
    fds = getSystem(systems, "Famicom Disk System");
    dreamcast = getSystem(systems, "Sega Dreamcast");
    gamegear = getSystem(systems, "Sega Gamegear");
    genesis = getSystem(systems, "Sega Genesis");
    mastersystem = getSystem(systems, "Sega Master System");
    megadrive = getSystem(systems, "Sega Mega Drive");
    saturn = getSystem(systems, "Sega Saturn");
    sega32x = getSystem(systems, "Sega 32x");
    segacd = getSystem(systems, "Sega CD");
    sg1000 = getSystem(systems, "Sega GS - 1000");
    neogeo = getSystem(systems, "Neo Geo");
    ngp = getSystem(systems, "Neo Geo Pocket");
    ngpc = getSystem(systems, "Neo Geo Pocket Color");
    wonderswan = getSystem(systems, "Wonderswan");
    wonderswancolor = getSystem(systems, "Wonderswan Color");
    psx = getSystem(systems, "Playstation");
    ps2 = getSystem(systems, "Playstation 2");
    psp = getSystem(systems, "Playstation Portable");
    atari2600 = getSystem(systems, "Atari 2600");
    atari7800 = getSystem(systems, "Atari 7800 Prosystem");
    atarijaguar = getSystem(systems, "Atari Jaguar");
    atarilynx = getSystem(systems, "Atari Lynx");
    atarist = getSystem(systems, "Atari ST, STE, Falcon");
    c64 = getSystem(systems, "Commodore 64");
    amiga = getSystem(systems, "Amiga");
    msx = getSystem(systems, "MSX");
    zxspectrum = getSystem(systems, "ZX Spectrum");
    pc = getSystem(systems, "PC (x86)");
    fba = getSystem(systems, "Final Burn Alpha");
    vectrex = getSystem(systems, "Vectrex");
    threeDo = getSystem(systems, "3do");
    pcengine = getSystem(systems, "TurboGrafx 16 (PC Engine)");
    pcfx = getSystem(systems, "PC-FX");
    videopac = getSystem(systems, "Odyssey 2 / Videopac");
    virtualboy = getSystem(systems, "Virtual Boy");
    love = getSystem(systems, "LOVE");
    mame = getSystem(systems, "MAME");
    scummvm = getSystem(systems, "ScummVM");
}

void testsystems_destroy() {
    if (systems != NULL) {
        destroySystems(systems);
    }
}