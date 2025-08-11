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

extern rl_system *gb;
extern rl_system *gbc;
extern rl_system *gba;
extern rl_system *nes;
extern rl_system *snes;
extern rl_system *gc;
extern rl_system *nds;
extern rl_system *n64;
extern rl_system *wii;
extern rl_system *wiiu;
extern rl_system *gw;
extern rl_system *fds;
extern rl_system *dreamcast;
extern rl_system *gamegear;
extern rl_system *genesis;
extern rl_system *mastersystem;
extern rl_system *megadrive;
extern rl_system *saturn;
extern rl_system *sega32x;
extern rl_system *segacd;
extern rl_system *sg1000;
extern rl_system *database_systemAdd;
extern rl_system *neogeo;
extern rl_system *ngp;
extern rl_system *ngpc;
extern rl_system *wonderswan;
extern rl_system *wonderswancolor;
extern rl_system *psx;
extern rl_system *ps2;
extern rl_system *psp;
extern rl_system *atari2600;
extern rl_system *atari7800;
extern rl_system *atarijaguar;
extern rl_system *atarilynx;
extern rl_system *atarist;
extern rl_system *c64;
extern rl_system *amiga;
extern rl_system *msx;
extern rl_system *zxspectrum;
extern rl_system *pc;
extern rl_system *fba;
extern rl_system *vectrex;
extern rl_system *threeDo;
extern rl_system *pcengine;
extern rl_system *pcfx;
extern rl_system *videopac;
extern rl_system *virtualboy;
extern rl_system *love;
extern rl_system *mame;
extern rl_system *scummvm;

void testsystems_init();

void testsystems_destroy();

#endif
