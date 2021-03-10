#pragma once
#include "AutomotaGrid.h"

class Renderer
{
private:
	AutomotaGrid* automota;

public:
	unsigned int w = 100, h = 100;
	bool* Frame;

	Renderer(AutomotaGrid* _automata) {
		automota = _automata;
		Frame = new bool[w * h];
	}

	void RenderFrame() {
		float step_x = 2.0f / w;
		float step_y = 2.0f/ h;

		for (float x = -1, y = -1; y <= 1;) {
			RenderViewRay(x, y);

			x+=step_x;
			if (x >= 1) { x = -1; y += step_y; }
		}
	}

	bool RenderViewRay(float x, float y) {

	}
};

