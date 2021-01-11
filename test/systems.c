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

    gb = getSystem(findSystemByFullname(systems, "Game Boy"));
    gbc = getSystem(findSystemByFullname(systems, "Game Boy Color"));
    gba = getSystem(findSystemByFullname(systems, "Game Boy Advance"));
    nes = getSystem(findSystemByFullname(systems, "Nintendo Entertainment System"));
    snes = getSystem(findSystemByFullname(systems, "Super Nintendo Entertainment System"));
    gc = getSystem(findSystemByFullname(systems, "Nintendo GameCube"));
    nds = getSystem(findSystemByFullname(systems, "Nintendo DS"));
    n64 = getSystem(findSystemByFullname(systems, "Nintendo 64"));
    wii = getSystem(findSystemByFullname(systems, "Nintendo Wii"));
    wiiu = getSystem(findSystemByFullname(systems, "Nintendo Wii U"));
    gw = getSystem(findSystemByFullname(systems, "Game and Watch"));
    fds = getSystem(findSystemByFullname(systems, "Famicom Disk System"));
    dreamcast = getSystem(findSystemByFullname(systems, "Sega Dreamcast"));
    gamegear = getSystem(findSystemByFullname(systems, "Sega Gamegear"));
    genesis = getSystem(findSystemByFullname(systems, "Sega Genesis"));
    mastersystem = getSystem(findSystemByFullname(systems, "Sega Master System"));
    megadrive = getSystem(findSystemByFullname(systems, "Sega Mega Drive"));
    saturn = getSystem(findSystemByFullname(systems, "Sega Saturn"));
    sega32x = getSystem(findSystemByFullname(systems, "Sega 32x"));
    segacd = getSystem(findSystemByFullname(systems, "Sega CD"));
    sg1000 = getSystem(findSystemByFullname(systems, "Sega GS - 1000"));
    neogeo = getSystem(findSystemByFullname(systems, "Neo Geo"));
    ngp = getSystem(findSystemByFullname(systems, "Neo Geo Pocket"));
    ngpc = getSystem(findSystemByFullname(systems, "Neo Geo Pocket Color"));
    wonderswan = getSystem(findSystemByFullname(systems, "Wonderswan"));
    wonderswancolor = getSystem(findSystemByFullname(systems, "Wonderswan Color"));
    psx = getSystem(findSystemByFullname(systems, "Playstation"));
    ps2 = getSystem(findSystemByFullname(systems, "Playstation 2"));
    psp = getSystem(findSystemByFullname(systems, "Playstation Portable"));
    atari2600 = getSystem(findSystemByFullname(systems, "Atari 2600"));
    atari7800 = getSystem(findSystemByFullname(systems, "Atari 7800 Prosystem"));
    atarijaguar = getSystem(findSystemByFullname(systems, "Atari Jaguar"));
    atarilynx = getSystem(findSystemByFullname(systems, "Atari Lynx"));
    atarist = getSystem(findSystemByFullname(systems, "Atari ST, STE, Falcon"));
    c64 = getSystem(findSystemByFullname(systems, "Commodore 64"));
    amiga = getSystem(findSystemByFullname(systems, "Amiga"));
    msx = getSystem(findSystemByFullname(systems, "MSX"));
    zxspectrum = getSystem(findSystemByFullname(systems, "ZX Spectrum"));
    pc = getSystem(findSystemByFullname(systems, "PC (x86)"));
    fba = getSystem(findSystemByFullname(systems, "Final Burn Alpha"));
    vectrex = getSystem(findSystemByFullname(systems, "Vectrex"));
    threeDo = getSystem(findSystemByFullname(systems, "3do"));
    pcengine = getSystem(findSystemByFullname(systems, "TurboGrafx 16 (PC Engine)"));
    pcfx = getSystem(findSystemByFullname(systems, "PC-FX"));
    videopac = getSystem(findSystemByFullname(systems, "Odyssey 2 / Videopac"));
    virtualboy = getSystem(findSystemByFullname(systems, "Virtual Boy"));
    love = getSystem(findSystemByFullname(systems, "LOVE"));
    mame = getSystem(findSystemByFullname(systems, "MAME"));
    scummvm = getSystem(findSystemByFullname(systems, "ScummVM"));
}

void testsystems_destroy() {
    if (systems != NULL) {
        destroySystems(systems);
    }
}