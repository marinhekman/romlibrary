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
    systems = rl_systems_init();

    gb = rl_getSystem(rl_systems_findByFullname(systems, "Game Boy"));
    gbc = rl_getSystem(rl_systems_findByFullname(systems, "Game Boy Color"));
    gba = rl_getSystem(rl_systems_findByFullname(systems, "Game Boy Advance"));
    nes = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo Entertainment System"));
    snes = rl_getSystem(rl_systems_findByFullname(systems, "Super Nintendo Entertainment System"));
    gc = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo GameCube"));
    nds = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo DS"));
    n64 = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo 64"));
    wii = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo Wii"));
    wiiu = rl_getSystem(rl_systems_findByFullname(systems, "Nintendo Wii U"));
    gw = rl_getSystem(rl_systems_findByFullname(systems, "Game and Watch"));
    fds = rl_getSystem(rl_systems_findByFullname(systems, "Famicom Disk System"));
    dreamcast = rl_getSystem(rl_systems_findByFullname(systems, "Sega Dreamcast"));
    gamegear = rl_getSystem(rl_systems_findByFullname(systems, "Sega Gamegear"));
    genesis = rl_getSystem(rl_systems_findByFullname(systems, "Sega Genesis"));
    mastersystem = rl_getSystem(rl_systems_findByFullname(systems, "Sega Master System"));
    megadrive = rl_getSystem(rl_systems_findByFullname(systems, "Sega Mega Drive"));
    saturn = rl_getSystem(rl_systems_findByFullname(systems, "Sega Saturn"));
    sega32x = rl_getSystem(rl_systems_findByFullname(systems, "Sega 32x"));
    segacd = rl_getSystem(rl_systems_findByFullname(systems, "Sega CD"));
    sg1000 = rl_getSystem(rl_systems_findByFullname(systems, "Sega GS - 1000"));
    neogeo = rl_getSystem(rl_systems_findByFullname(systems, "Neo Geo"));
    ngp = rl_getSystem(rl_systems_findByFullname(systems, "Neo Geo Pocket"));
    ngpc = rl_getSystem(rl_systems_findByFullname(systems, "Neo Geo Pocket Color"));
    wonderswan = rl_getSystem(rl_systems_findByFullname(systems, "Wonderswan"));
    wonderswancolor = rl_getSystem(rl_systems_findByFullname(systems, "Wonderswan Color"));
    psx = rl_getSystem(rl_systems_findByFullname(systems, "Playstation"));
    ps2 = rl_getSystem(rl_systems_findByFullname(systems, "Playstation 2"));
    psp = rl_getSystem(rl_systems_findByFullname(systems, "Playstation Portable"));
    atari2600 = rl_getSystem(rl_systems_findByFullname(systems, "Atari 2600"));
    atari7800 = rl_getSystem(rl_systems_findByFullname(systems, "Atari 7800 Prosystem"));
    atarijaguar = rl_getSystem(rl_systems_findByFullname(systems, "Atari Jaguar"));
    atarilynx = rl_getSystem(rl_systems_findByFullname(systems, "Atari Lynx"));
    atarist = rl_getSystem(rl_systems_findByFullname(systems, "Atari ST, STE, Falcon"));
    c64 = rl_getSystem(rl_systems_findByFullname(systems, "Commodore 64"));
    amiga = rl_getSystem(rl_systems_findByFullname(systems, "Amiga"));
    msx = rl_getSystem(rl_systems_findByFullname(systems, "MSX"));
    zxspectrum = rl_getSystem(rl_systems_findByFullname(systems, "ZX Spectrum"));
    pc = rl_getSystem(rl_systems_findByFullname(systems, "PC (x86)"));
    fba = rl_getSystem(rl_systems_findByFullname(systems, "Final Burn Alpha"));
    vectrex = rl_getSystem(rl_systems_findByFullname(systems, "Vectrex"));
    threeDo = rl_getSystem(rl_systems_findByFullname(systems, "3do"));
    pcengine = rl_getSystem(rl_systems_findByFullname(systems, "TurboGrafx 16 (PC Engine)"));
    pcfx = rl_getSystem(rl_systems_findByFullname(systems, "PC-FX"));
    videopac = rl_getSystem(rl_systems_findByFullname(systems, "Odyssey 2 / Videopac"));
    virtualboy = rl_getSystem(rl_systems_findByFullname(systems, "Virtual Boy"));
    love = rl_getSystem(rl_systems_findByFullname(systems, "LOVE"));
    mame = rl_getSystem(rl_systems_findByFullname(systems, "MAME"));
    scummvm = rl_getSystem(rl_systems_findByFullname(systems, "ScummVM"));
}

void testsystems_destroy() {
    if (systems != NULL) {
        rl_system_free(systems);
    }
}