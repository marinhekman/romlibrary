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

#include <romlibrary.h>
#include <string.h>

static system_t *createSystem(char *name, char *fullname, char *path, int active);

acll_t *systems_init() {
    acll_t *systems = NULL;
    systems = acll_push(systems, createSystem("gb", "Game Boy", "/gb", 1));
    systems = acll_push(systems, createSystem("gba", "Game Boy Advance", "/gba", 1));
    systems = acll_push(systems, createSystem("gbc", "Game Boy Color", "/gbc", 1));
    systems = acll_push(systems, createSystem("nes", "Nintendo Entertainment System", "/nes", 1));
    systems = acll_push(systems,
                        createSystem("snes", "Super Nintendo Entertainment System", "/snes", 1));
    systems = acll_push(systems, createSystem("gc", "Nintendo GameCube", "/gc", 1));
    systems = acll_push(systems, createSystem("nds", "Nintendo DS", "/nds", 1));
    systems = acll_push(systems, createSystem("n64", "Nintendo 64", "/n64", 1));
    systems = acll_push(systems, createSystem("wii", "Nintendo Wii", "/wii", 1));
    systems = acll_push(systems, createSystem("wiiu", "Nintendo Wii U", "/wiiu", 1));
    systems = acll_push(systems, createSystem("gw", "Game and Watch", "/gw", 1));
    systems = acll_push(systems, createSystem("fds", "Famicom Disk System", "/fds", 1));

    systems = acll_push(systems, createSystem("dreamcast", "Sega Dreamcast", "/dreamcast", 1));
    systems = acll_push(systems, createSystem("gamegear", "Sega Gamegear", "/gamegear", 1));
    systems = acll_push(systems, createSystem("genesis", "Sega Genesis", "/genesis", 1));
    systems = acll_push(systems, createSystem("mastersystem", "Sega Master System", "/mastersystem", 1));
    systems = acll_push(systems, createSystem("megadrive", "Sega Mega Drive", "/megadrive", 1));
    systems = acll_push(systems, createSystem("saturn", "Sega Saturn", "/saturn", 1));
    systems = acll_push(systems, createSystem("sega32x", "Sega 32x", "/sega32x", 1));
    systems = acll_push(systems, createSystem("segacd", "Sega CD", "/segacd", 1));
    systems = acll_push(systems, createSystem("sg-1000", "Sega GS - 1000", "/sg-1000", 1));

    systems = acll_push(systems, createSystem("neogeo", "Neo Geo", "/neogeo", 1));
    systems = acll_push(systems, createSystem("ngp", "Neo Geo Pocket", "/ngp", 1));
    systems = acll_push(systems, createSystem("ngpc", "Neo Geo Pocket Color", "/ngpc", 1));
    systems = acll_push(systems, createSystem("wonderswan", "Wonderswan", "/wonderswan", 1));
    systems = acll_push(systems,
                        createSystem("wonderswancolor", "Wonderswan Color", "/wonderswancolor", 1));

    systems = acll_push(systems, createSystem("psx", "Playstation", "/psx", 1));
    systems = acll_push(systems, createSystem("ps2", "Playstation 2", "/ps2", 1));
    systems = acll_push(systems, createSystem("psp", "Playstation Portable", "/psp", 1));

    systems = acll_push(systems, createSystem("atari2600", "Atari 2600", "/atari2600", 1));
    systems = acll_push(systems, createSystem("atari7800", "Atari 7800 Prosystem", "/atari7800", 1));
    systems = acll_push(systems, createSystem("atarijaguar", "Atari Jaguar", "/atarijaguar", 1));
    systems = acll_push(systems, createSystem("atarilynx", "Atari Lynx", "/atarilynx", 1));
    systems = acll_push(systems, createSystem("atarist", "Atari ST, STE, Falcon", "/atarist", 1));

    systems = acll_push(systems, createSystem("c64", "Commodore 64", "/c64", 1));
    systems = acll_push(systems, createSystem("amiga", "Amiga", "/amiga", 1));
    systems = acll_push(systems, createSystem("msx", "MSX", "/msx", 1));
    systems = acll_push(systems, createSystem("zxspectrum", "ZX Spectrum", "/zxspectrum", 1));
    systems = acll_push(systems, createSystem("pc", "PC (x86)", "/pc", 1));

    systems = acll_push(systems, createSystem("fba", "Final Burn Alpha", "/fba", 1));
    systems = acll_push(systems, createSystem("vectrex", "Vectrex", "/vectrex", 1));

    systems = acll_push(systems, createSystem("3do", "3do", "/3do", 1));
    systems = acll_push(systems, createSystem("pcengine", "TurboGrafx 16 (PC Engine)", "/pcengine", 1));
    systems = acll_push(systems, createSystem("pcfx", "PC-FX", "/pcfx", 1));
    systems = acll_push(systems, createSystem("videopac", "Odyssey 2 / Videopac", "/videopac", 1));
    systems = acll_push(systems, createSystem("virtualboy", "Virtual Boy", "/virtualboy", 1));

    systems = acll_push(systems, createSystem("love", "LOVE", "/love", 1));
    systems = acll_push(systems, createSystem("mame", "MAME", "/mame", 1));
    systems = acll_push(systems, createSystem("scummvm", "ScummVM", "/scummvm", 1));

    return systems;
}

void systems_destroy(acll_t *systems) {
    acll_free(systems, NULL);
}

int system_findByFullname(void *payload, void *input) {
    system_t *system = payload;
    char *fullname = input;

    return !strcmp(system->fullname, fullname);
}

static system_t *createSystem(char *name, char *fullname, char *path, int active) {
    system_t *system = calloc(1, sizeof(system_t));
    system->name = name;
    system->fullname = fullname;
    system->active = active;
    system->path = path;
    return system;
}