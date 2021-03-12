#pragma once
#include "AutomotaGrid.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

int CountAliveNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 1> _automataGrid, unsigned int w, unsigned int h, unsigned int l) restrict(amp, cpu) {
	int alive = 0;

	for (int _x = x - 1, _y = y - 1, _z = z - 1; _z <= z + 1;) {
		if (_x==x&&_y==y&&_z==z){ }
		else if (_x >= 0 && _y >= 0 && _z >= 0 && _x <= w && _y <= h && _z <= l) {

			if (!_automataGrid[_x + (_y * w) + (_z * h * w)].IsBlack()) alive++;
		}

		_x++;
		if (_x > x + 1) { _x = x - 1; _y++; }
		if (_y > y + 1) { _y = y - 1; _z++; }
	}

	return alive;
}

void GameOfLife(AutomotaGrid* automata) {
	array_view<Color, 1> _automataGrid(automata->w * automata->h * automata->l, automata->Grid);
	array_view<Color, 1> _newGrid(automata->w * automata->h * automata->l, automata->Grid);

	unsigned int w = automata->w;
	unsigned int h = automata->h;
	unsigned int l = automata->l;

	parallel_for_each(
		_automataGrid.extent,
		[=](index<1> idx) restrict(amp) {

			bool amIBlack = _automataGrid[idx].IsBlack();
			int alive = CountAliveNeighbours(idx[0] % w, (idx[0] / w) % h, idx[0]/w/h, _automataGrid, w,h,l);
			
			if (alive < 2) _newGrid[idx] = Color(0, 0, 0);
			else if (alive > 3) _newGrid[idx] = Color(0, 0, 0);
			else if (alive == 3 && amIBlack) _newGrid[idx] = Color(UINT_MAX, UINT_MAX, UINT_MAX);
			else if (!amIBlack) _newGrid[idx] = _automataGrid[idx];
		}
	);

	_newGrid.synchronize(access_type_write);
}


