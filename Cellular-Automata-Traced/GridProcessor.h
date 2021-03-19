#pragma once
#include "AutomotaGrid.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

int CountAliveNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid, unsigned int w, unsigned int h, unsigned int l) restrict(amp, cpu) {
	int alive = 0;
	
	alive += !_automataGrid[x - 1][y - 1][x - 1].IsBlack();
	alive += !_automataGrid[x][y - 1][x - 1].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][x - 1].IsBlack();

	alive += !_automataGrid[x - 1][y][x - 1].IsBlack();
	alive += !_automataGrid[x][y][x - 1].IsBlack();
	alive += !_automataGrid[x + 1][y][x - 1].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][x - 1].IsBlack();
	alive += !_automataGrid[x][y + 1][x - 1].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][x - 1].IsBlack();

	alive += !_automataGrid[x - 1][y - 1][x].IsBlack();
	alive += !_automataGrid[x][y - 1][x].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][x].IsBlack();

	alive += !_automataGrid[x - 1][y][x].IsBlack();
	alive += !_automataGrid[x + 1][y][x].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][x].IsBlack();
	alive += !_automataGrid[x][y + 1][x].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][x].IsBlack();

	alive += !_automataGrid[x - 1][y - 1][x + 1].IsBlack();
	alive += !_automataGrid[x][y - 1][x + 1].IsBlack();
	alive += !_automataGrid[x + 1][y - 1][x + 1].IsBlack();

	alive += !_automataGrid[x - 1][y][x + 1].IsBlack();
	alive += !_automataGrid[x][y][x + 1].IsBlack();
	alive += !_automataGrid[x + 1][y][x + 1].IsBlack();

	alive += !_automataGrid[x - 1][y + 1][x + 1].IsBlack();
	alive += !_automataGrid[x][y + 1][x + 1].IsBlack();
	alive += !_automataGrid[x + 1][y + 1][x + 1].IsBlack();

	return alive;
}

completion_future GameOfLife(AutomotaGrid* automata) {
	const unsigned int w = automata->w;
	const unsigned int h = automata->h;
	const unsigned int l = automata->l;

	array_view<Color, 3> _automataGrid(w, h, l, automata->Grid);
	array_view<Color, 3> _newGrid(w, h, l, automata->Grid);

	parallel_for_each(
		_automataGrid.extent,
		[=](index<3> idx) restrict(amp) {
			bool amIBlack = _automataGrid[idx].IsBlack();
			int alive = CountAliveNeighbours(idx[2], idx[1], idx[0], _automataGrid, w, h, l);

			if (alive < 2) _newGrid[idx] = Color(0, 0, 0);
			else if (alive > 4) _newGrid[idx] = Color(0, 0, 0);
			else if (alive > 5 && amIBlack) _newGrid[idx] = Color(UINT_MAX, UINT_MAX, UINT_MAX);
			else _newGrid[idx] = _automataGrid[idx];
		}
	);

	/*for (int x = 0, y = 0, z = 0; z < l;) {
		int alive = CountAliveNeighbours(z, y, x, _automataGrid, w, h, l);

			if (alive >= 0) _automataGrid[z][y][x] = Color(0, 0, 0);
			else _automataGrid[z][y][x] = _automataGrid[z][y][x];

		x++;
		if (x == w) { x = 0; y++; }
		if (y == h) { y = 0; z++; }
	}*/

	return _newGrid.synchronize_async(access_type_read_write);
}
