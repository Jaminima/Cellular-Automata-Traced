#pragma once
#include "AutomotaGrid.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

int CountAliveNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid, unsigned int w, unsigned int h, unsigned int l) restrict(amp, cpu) {
	int alive = 0;

	alive += !_automataGrid[x - 1][y - 1][z - 1].IsBlack();
	alive += !_automataGrid[x][y - 1][z - 1].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][z - 1].IsBlack();

	alive += !_automataGrid[x - 1][y][z - 1].IsBlack();
	alive += !_automataGrid[x][y][z - 1].IsBlack();
	alive += !_automataGrid[x + 1][y][z - 1].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][z - 1].IsBlack();
	alive += !_automataGrid[x][y + 1][z - 1].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][z - 1].IsBlack();

	alive += !_automataGrid[x - 1][y - 1][z].IsBlack();
	alive += !_automataGrid[x][y - 1][z].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][z].IsBlack();

	alive += !_automataGrid[x - 1][y][z].IsBlack();
	alive += !_automataGrid[x + 1][y][z].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][z].IsBlack();
	alive += !_automataGrid[x][y + 1][z].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][z].IsBlack();

	alive += !_automataGrid[x - 1][y - 1][z + 1].IsBlack();
	alive += !_automataGrid[x][y - 1][z + 1].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][z + 1].IsBlack();

	alive += !_automataGrid[x - 1][y][z + 1].IsBlack();
	alive += !_automataGrid[x][y][z + 1].IsBlack();
	alive += !_automataGrid[x + 1][y][z + 1].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][z + 1].IsBlack();
	alive += !_automataGrid[x][y + 1][z + 1].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][z + 1].IsBlack();

	return alive;
}

void GameOfLife(AutomotaGrid* automata) {
	unsigned int w = automata->w;
	unsigned int h = automata->h;
	unsigned int l = automata->l;

	array_view<Color, 3> _automataGrid(w , h , l, automata->Grid);
	array_view<Color, 3> _newGrid(w , h , l, automata->Grid);

	parallel_for_each(
		_automataGrid.extent,
		[=](index<3> idx) restrict(amp) {

			bool amIBlack = _automataGrid[idx].IsBlack();
			int alive = CountAliveNeighbours(idx[2], idx[1], idx[0], _automataGrid, w,h,l);
			
			if (alive < 2) _newGrid[idx] = Color(0, 0, 0);
			else if (alive > 2) _newGrid[idx] = Color(0, 0, 0);
			else if (alive > 3 && amIBlack) _newGrid[idx] = Color(UINT_MAX, UINT_MAX, UINT_MAX);
			else if (!amIBlack) _newGrid[idx] = _automataGrid[idx];
			else _newGrid[idx] = _automataGrid[idx];
		}
	);

	_newGrid.synchronize(access_type_write);
}


