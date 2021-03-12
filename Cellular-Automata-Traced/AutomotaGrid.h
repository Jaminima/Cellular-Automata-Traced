#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Color.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

class AutomotaGrid
{
private:

	void InitGrid() {
		srand(time(NULL));
		Grid = new Color[h*w*l];

		for (unsigned int i = 0; i < h * w * l; i++) {
			int r = rand() % 100;
			if (r == 0) Grid[i] = Color(UINT_MAX, UINT_MAX, UINT_MAX);
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

	Color* GetCellNeighbours(unsigned int x, unsigned int y, unsigned int z) {
		Color* cells = new Color[9];
		char i = 0;

		for (int _x = x - 1, _y = y - 1, _z = z - 1; _z <= z + 1; i++) {
			if (_x >= 0 && _y >= 0 && _z >= 0 && _x <= w && _y <= h && _z <= l)
				cells[i] = Grid[_x + (_y * w) + (_z * h * w)];

			_x++;
			if (_x > x + 1) { _x = x - 1; _y++; }
			if (_y > y + 1) { _y = y - 1; _z++; }
		}

		return cells;
	}
};
