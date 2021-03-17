#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Color.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

const unsigned int mul = UINT_MAX / RAND_MAX;

class AutomotaGrid
{
private:

	void InitGrid() {
		srand(time(NULL));
		Grid = new Color[h * w * l];

		for (unsigned int i = 0; i < h * w * l; i++) {
			int r = rand() % 10;
			if (r == 0) Grid[i] = Color(rand() * mul, rand() * mul, rand() * mul);
			else Grid[i] = Color(0, 0, 0);
		}
	}

public:
	Color* Grid;
	unsigned int w = 200, h = 200, l = 200;

	AutomotaGrid() {
		this->InitGrid();
	}

	void SetState(unsigned int x, unsigned int y, unsigned int z, Color State) {
		Grid[x + (y * w) + (z * w * h)] = State;
	}

	AutomotaGrid(unsigned int w, unsigned int h, unsigned int l) {
		this->h = h;
		this->w = w;
		this->l = l;
		this->InitGrid();
	}
};
