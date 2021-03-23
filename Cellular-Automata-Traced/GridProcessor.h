#pragma once
#include "AutomotaGrid.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

struct Neighbours {
public:
	Color average;
	int alive;

	Neighbours(Color _average, int _alive) restrict(amp, cpu) {
		average = _average;
		alive = _alive;
	}
};

int CountAliveNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid, unsigned int w, unsigned int h, unsigned int l) restrict(amp, cpu) {
	int alive = 0;

	alive += !_automataGrid[z - 1][y - 1][x - 1].IsBlack();
	alive += !_automataGrid[z][y - 1][x - 1].IsBlack();
	alive += !_automataGrid[z + 1][y - 1][x - 1].IsBlack();

	alive += !_automataGrid[z - 1][y][x - 1].IsBlack();
	alive += !_automataGrid[z][y][x - 1].IsBlack();
	alive += !_automataGrid[z + 1][y][x - 1].IsBlack();

	alive += !_automataGrid[z - 1][y + 1][x - 1].IsBlack();
	alive += !_automataGrid[z][y + 1][x - 1].IsBlack();
	alive += !_automataGrid[z + 1][y + 1][x - 1].IsBlack();

	alive += !_automataGrid[z - 1][y - 1][x].IsBlack();
	alive += !_automataGrid[z][y - 1][x].IsBlack();
	alive += !_automataGrid[z + 1][y - 1][x].IsBlack();

	alive += !_automataGrid[z - 1][y][x].IsBlack();
	alive += !_automataGrid[z + 1][y][x].IsBlack();

	alive += !_automataGrid[z - 1][y + 1][x].IsBlack();
	alive += !_automataGrid[z][y + 1][x].IsBlack();
	alive += !_automataGrid[z + 1][y + 1][x].IsBlack();

	alive += !_automataGrid[z - 1][y - 1][x + 1].IsBlack();
	alive += !_automataGrid[z][y - 1][x + 1].IsBlack();
	alive += !_automataGrid[z + 1][y - 1][x + 1].IsBlack();

	alive += !_automataGrid[z - 1][y][x + 1].IsBlack();
	alive += !_automataGrid[z][y][x + 1].IsBlack();
	alive += !_automataGrid[z + 1][y][x + 1].IsBlack();

	alive += !_automataGrid[z - 1][y + 1][x + 1].IsBlack();
	alive += !_automataGrid[z][y + 1][x + 1].IsBlack();
	alive += !_automataGrid[z + 1][y + 1][x + 1].IsBlack();

	return alive;
}

Color AverageOfNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid, unsigned int w, unsigned int h, unsigned int l) restrict(amp, cpu) {
	Color average = _automataGrid[z - 1][y - 1][x - 1]
		+ _automataGrid[z][y - 1][x - 1]
		+ _automataGrid[z + 1][y - 1][x - 1]

		+ _automataGrid[z - 1][y][x - 1]
		+ _automataGrid[z][y][x - 1]
		+ _automataGrid[z + 1][y][x - 1]

		+ _automataGrid[z - 1][y + 1][x - 1]
		+ _automataGrid[z][y + 1][x - 1]
		+ _automataGrid[z + 1][y + 1][x - 1]

		+ _automataGrid[z - 1][y - 1][x]
		+ _automataGrid[z][y - 1][x]
		+ _automataGrid[z + 1][y - 1][x]

		+ _automataGrid[z - 1][y][x]
		+ _automataGrid[z + 1][y][x]

		+ _automataGrid[z - 1][y + 1][x]
		+ _automataGrid[z][y + 1][x]
		+ _automataGrid[z + 1][y + 1][x]

		+ _automataGrid[z - 1][y - 1][x + 1]
		+ _automataGrid[z][y - 1][x + 1]
		+ _automataGrid[z + 1][y - 1][x + 1]

		+ _automataGrid[z - 1][y][x + 1]
		+ _automataGrid[z][y][x + 1]
		+ _automataGrid[z + 1][y][x + 1]

		+ _automataGrid[z - 1][y + 1][x + 1]
		+ _automataGrid[z][y + 1][x + 1]
		+ _automataGrid[z + 1][y + 1][x + 1];

	return average;
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

			if (alive == 4 && amIBlack) _newGrid[idx] = AverageOfNeighbours(idx[2], idx[1], idx[0], _automataGrid, w, h, l);
			else if ((alive < 4 || alive > 5)&& !amIBlack) _newGrid[idx] = Color(0,0,0);
			else _newGrid[idx] = _automataGrid[idx];
		}
	);

	return _newGrid.synchronize_async(access_type_read_write);
}
