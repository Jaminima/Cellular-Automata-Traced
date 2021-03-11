#pragma once
#include "AutomotaGrid.h"
#include "vec3.h"
#include "Camera.h"

class Renderer
{
private:
	AutomotaGrid* automota;
	Camera camera = Camera();

public:
	unsigned int w = 100, h = 100;
	unsigned int maxView = 4;
	bool* Frame;

	Renderer(AutomotaGrid* _automata) {
		automota = _automata;
		Frame = new bool[w * h];
	}

	void RenderFrame() {
		float step_x = 2.0f / w;
		float step_y = 2.0f/ h;
		unsigned int i = 0;

		for (float x = -1, y = -1; y <= 1;i++) {
			RenderViewRay(x, y, i);

			x+=step_x;
			if (x >= 1) { x = -1; y += step_y; }
		}
	}

	void OntoConsole() {
		for (unsigned int x = 0, y = 0; y < h;) {
			if (Frame[x + (y * w)]) std::cout << '1';
			else std::cout << '0';
			x++;
			if (x == w) { x = 0; y++; std::cout << '\n'; }
		}
	}

	void RenderViewRay(float x, float y, unsigned int i) {
		Vec3 dir(x,y,1);
		dir = camera.RotateDirection(dir);

		for (int j = 0; j < maxView; j++) {
			Vec3 Cell = (dir * j) + camera.Position;

			unsigned int indx = roundf(Cell.x) + (roundf(Cell.y)*automota->w) + (roundf(Cell.z)*automota->w*automota->h);

			if (automota->Grid[indx]) {
				Frame[i] = true;
				return;
			}
		}
		Frame[i] = false;
	}
};

