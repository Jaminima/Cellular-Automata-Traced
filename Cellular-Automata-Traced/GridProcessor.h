#pragma once
#include "AutomotaGrid.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;

void GameOfLife(AutomotaGrid* automata) {

	array_view<Color, 1> _automataGrid(automata->w * automata->h * automata->l, automata->Grid);

	parallel_for_each(
		_automataGrid.extent,
		[=](index<1> idx) restrict(amp) {
			if (!_automataGrid[idx - 1].IsBlack()) _automataGrid[idx] = _automataGrid[idx - 1];
			if (!_automataGrid[idx + 1].IsBlack()) _automataGrid[idx] = Color(0,0,0);
		}
	);
}