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

#ifndef TEST_SYSTEMS_H
#define TEST_SYSTEMS_H

#include <romlibrary.h>

rl_system *gb;
rl_system *gbc;
rl_system *gba;
rl_system *nes;
rl_system *snes;
rl_system *gc;
rl_system *nds;
rl_system *n64;
rl_system *wii;
rl_system *wiiu;
rl_system *gw;
rl_system *fds;
rl_system *dreamcast;
rl_system *gamegear;
rl_system *genesis;
rl_system *mastersystem;
rl_system *megadrive;
rl_system *saturn;
rl_system *sega32x;
rl_system *segacd;
rl_system *sg1000;
rl_system *database_systemAdd;
rl_system *neogeo;
rl_system *ngp;
rl_system *ngpc;
rl_system *wonderswan;
rl_system *wonderswancolor;
rl_system *psx;
rl_system *ps2;
rl_system *psp;
rl_system *atari2600;
rl_system *atari7800;
rl_system *atarijaguar;
rl_system *atarilynx;
rl_system *atarist;
rl_system *c64;
rl_system *amiga;
rl_system *msx;
rl_system *zxspectrum;
rl_system *pc;
rl_system *fba;
rl_system *vectrex;
rl_system *threeDo;
rl_system *pcengine;
rl_system *pcfx;
rl_system *videopac;
rl_system *virtualboy;
rl_system *love;
rl_system *mame;
rl_system *scummvm;

void testsystems_init();

void testsystems_destroy();

#endif
