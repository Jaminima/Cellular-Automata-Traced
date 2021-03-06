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

int CountAliveNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid) restrict(amp, cpu) {
	int alive = 0;

	for (int _x = -1, _y = -1; _y <= 1;) {
		alive += !_automataGrid[z - 1][y + _y][x + _x].IsBlack();
		alive += !_automataGrid[z][y + _y][x + _x].IsBlack();
		alive += !_automataGrid[z + 1][y + _y][x + _x].IsBlack();
		_x++;
		if (_x == 2) { _y++; _x = -1; }
	}

	return alive;
}

Color AverageOfNeighbours(unsigned int x, unsigned int y, unsigned int z, array_view<Color, 3> _automataGrid, unsigned int alive) restrict(amp, cpu) {
	Color average;
		
	for (int _x = -1, _y = -1; _y <= 1;) {
		average += _automataGrid[z - 1][y + _y][x + _x];
		average += _automataGrid[z][y + _y][x + _x];
		average += _automataGrid[z + 1][y + _y][x + _x];
		_x++;
		if (_x == 2) { _y++; _x = -1; }
	}

	average /= alive / 3.0f;

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
			int alive = CountAliveNeighbours(idx[2], idx[1], idx[0], _automataGrid);

			if (alive == 4 && amIBlack) _newGrid[idx] = AverageOfNeighbours(idx[2], idx[1], idx[0], _automataGrid, alive);
			else if (alive < 4 || alive > 4) _newGrid[idx] = Color(0, 0, 0);
			else _newGrid[idx] = _automataGrid[idx];
		}
	);

	return _newGrid.synchronize_async(access_type_read_write);
}
