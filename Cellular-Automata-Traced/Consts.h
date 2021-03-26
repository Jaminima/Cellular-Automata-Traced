#pragma once

//#define EnableReducedTracing

#ifndef __Consts
const unsigned int w = 1000, h = 1000;

const unsigned int w_half = w / 2, h_half = h / 2;

const unsigned int maxView = 100;

bool* doGameTicks = new bool();
AutomotaGrid* _automota = new AutomotaGrid();

const float camMoveStep = 0.5f;
const float camSensitvity = 0.001f;
#endif

#define __Consts
