#pragma once
#include "AutomotaGrid.h"
#include "vec3.h"
#include "Color.h"
#include "Camera.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;
using namespace fast_math;

	AutomotaGrid* automota;
	Camera* camera;

	unsigned int w = 1000, h = 1000;
	const unsigned int maxView = 20;
	Color* Frame;

	void Setup(AutomotaGrid* _automata, Camera* _camera) {
		automota = _automata;
		camera = _camera;

		camera->Position = Vec3(_automata->w / 2, _automata->h / 2, _automata->l / 2);
		Frame = new Color[w * h];
	}

	Color RenderViewRay(float x, float y, unsigned int i, array_view<int, 1> _automataGrid, Camera cam, unsigned int _aw, unsigned int _ah, unsigned int _al) restrict(amp, cpu) {
		Vec3 dir(x, y, 1);
		dir = cam.RotateDirection(dir);

		for (int j = 0; j < maxView; j++) {
			Vec3 Cell = (dir * j) + cam.Position;

			int indx = roundf(Cell.x) + (roundf(Cell.y) * _aw) + (roundf(Cell.z) * _aw * _ah);

			if (_automataGrid[indx / sizeof(int)] & (1UL << (indx % sizeof(int)))) {
				return Color(UINT_MAX, UINT_MAX, UINT_MAX);
			}
		}
		return Color(0, 0, 0);
	}

	void RenderFrame() {
		float step_x = 2.0f / w;
		float step_y = 2.0f / h;
		unsigned int i = 0;

		Camera cam = *camera;
		float _w = w, _h = h;

		unsigned int _aw = automota->w, _ah = automota->h, _al = automota->l;

		array_view<Color, 2> _Frame(w, h, Frame);
		array_view<int, 1> _automataGrid(automota->w * automota->h * automota->l / sizeof(int), (int*)automota->Grid);

		parallel_for_each(
			_Frame.extent,
			[=](index<2> idx) restrict(amp) {
				float vx = (idx[1] * step_x) - 1;
				float vy = (idx[0] * step_y) - 1;

				vx *= cam.fov;
				vy *= cam.fov * (_h / _w);

				_Frame[idx] = RenderViewRay(vx, vy, i, _automataGrid, cam, _aw, _ah, _al);
			}
		);

		_Frame.synchronize();
	}

	void OntoConsole() {
		for (unsigned int x = 0, y = 0; y < h;) {
			if (Frame[x + (y * w)].IsBlack()) std::cout << '1';
			else std::cout << '0';
			x++;
			if (x == w) { x = 0; y++; std::cout << '\n'; }
		}
	}

	

