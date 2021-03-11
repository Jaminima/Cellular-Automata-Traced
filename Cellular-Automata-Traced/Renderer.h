#pragma once
#include "AutomotaGrid.h"
#include "vec3.h"
#include "Color.h"
#include "Camera.h"

class Renderer
{
private:
	AutomotaGrid* automota;
	Camera *camera;

public:
	unsigned int w = 200, h = 200;
	unsigned int maxView = 10;
	Color* Frame;

	Renderer(AutomotaGrid* _automata, Camera *_camera) {
		automota = _automata;
		camera = _camera;

		camera->Position = Vec3(_automata->w / 2, _automata->h / 2, _automata->l / 2);
		Frame = new Color[w * h];
	}

	void RenderFrame() {
		double step_x = 2.0f / w;
		double step_y = 2.0f/ h;
		unsigned int i = 0;

		for (int x = 0, y = 0; y < h;i++) {
			RenderViewRay(x * step_x, y * step_y, i);

			x++;
			if (x >= w) { x = 0; y ++; }
		}
	}

	void OntoConsole() {
		for (unsigned int x = 0, y = 0; y < h;) {
			if (Frame[x + (y * w)].IsBlack()) std::cout << '1';
			else std::cout << '0';
			x++;
			if (x == w) { x = 0; y++; std::cout << '\n'; }
		}
	}

	void RenderViewRay(float x, float y, unsigned int i) {
		Vec3 dir(x,y,1);
		dir = camera->RotateDirection(dir);

		for (int j = 0; j < maxView; j++) {
			Vec3 Cell = (dir * j) + camera->Position;

			int indx = roundf(Cell.x) + (roundf(Cell.y)*automota->w) + (roundf(Cell.z)*automota->w*automota->h);

			if (automota->Grid[indx]) {
				Frame[i] = Color(UINT_MAX, UINT_MAX, UINT_MAX);
				return;
			}
		}
		Frame[i] = Color(0,0,0);
	}
};

