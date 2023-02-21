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

#include "mapping.h"
#include <string.h>

char *romhustler_deviceMapping(rl_system *system) {
    char *deviceString = NULL;

    if (!strcmp(system->name, "3do")) {
        deviceString = "3do";
    } else if (!strcmp(system->name, "atari2600")) {
        deviceString = "atari2600";
    } else if (!strcmp(system->name, "atari7800")) {
        deviceString = "atari7800";
    } else if (!strcmp(system->name, "atarijaguar")) {
        deviceString = "jaguar";
    } else if (!strcmp(system->name, "atarilynx")) {
        deviceString = "lynx";
    } else if (!strcmp(system->name, "dreamcast")) {
        deviceString = "dreamcast";
    } else if (!strcmp(system->name, "gamegear")) {
        deviceString = "gg";
    } else if (!strcmp(system->name, "gb")) {
        deviceString = "gbc";
    } else if (!strcmp(system->name, "gba")) {
        deviceString = "gba";
    } else if (!strcmp(system->name, "gbc")) {
        deviceString = "gbc";
    } else if (!strcmp(system->name, "gc")) {
        deviceString = "gamecube";
    } else if (!strcmp(system->name, "genesis") || !strcmp(system->name, "megadrive")) {
        deviceString = "genesis";
    } else if (!strcmp(system->name, "mame")) {
        deviceString = "mame";
    } else if (!strcmp(system->name, "mastersystem")) {
        deviceString = "sms";
    } else if (!strcmp(system->name, "msx")) {
        deviceString = "msx1";
    } else if (!strcmp(system->name, "n64")) {
        deviceString = "n64";
    } else if (!strcmp(system->name, "nds")) {
        deviceString = "nds";
    } else if (!strcmp(system->name, "neogeo")) {
        deviceString = "neogeo";
    } else if (!strcmp(system->name, "nes") || !strcmp(system->name, "fds")) {
        deviceString = "nes";
    } else if (!strcmp(system->name, "ngp")) {
        deviceString = "ngp";
    } else if (!strcmp(system->name, "ngpc")) {
        deviceString = "ngcd";
    } else if (!strcmp(system->name, "pcengine")) {
        deviceString = "pcengine";
    } else if (!strcmp(system->name, "psp")) {
        deviceString = "psp";
    } else if (!strcmp(system->name, "psx")) {
        deviceString = "psx";
    } else if (!strcmp(system->name, "saturn")) {
        deviceString = "saturn";
    } else if (!strcmp(system->name, "segacd")) {
        deviceString = "segacd";
    } else if (!strcmp(system->name, "snes")) {
        deviceString = "snes";
    } else if (!strcmp(system->name, "wonderswan")) {
        deviceString = "wonderswan";
    } else if (!strcmp(system->name, "wonderswancolor")) {
        deviceString = "wonderswan";
    }

    return deviceString;
}