#pragma once
#include "AutomotaGrid.h"
#include "vec3.h"
#include "Color.h"
#include "Camera.h"
#include "Consts.h"

#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;
using namespace fast_math;

AutomotaGrid* automota;
Camera* camera;

Color* Frame;

template <typename T> int sgn(T val) restrict(amp, cpu) {
	return (T(0) < val) - (val < T(0));
}

void Setup(AutomotaGrid* _automata, Camera* _camera) {
	automota = _automata;
	camera = _camera;

	//camera->Position = Vec3((_automata->w / 2) + 0.5f, (_automata->h / 2) + 0.5f, (_automata->l / 2) + 0.5f);
	camera->Position = Vec3(5, 5, 5);
	Frame = new Color[w * h];
}

struct Hit {
public:
	int axis = 0;
	float j = 0;

	Hit() restrict(amp, cpu) {}
	Hit(int _axis, float _j) restrict(amp, cpu) { axis = _axis; j = _j; }
};

Hit DetermineNextHop(Vec3 Dir, Vec3 Cell, Camera cam) restrict(amp, cpu) {
	Vec3 s = Vec3();

	if (Dir.x >= 0) s.x = ceilf(Cell.x);
	else s.x = floorf(Cell.x);

	if (Dir.y >= 0) s.y = ceilf(Cell.y);
	else s.y = floorf(Cell.y);

	if (Dir.z >= 0) s.z = ceilf(Cell.z);
	else s.z = floorf(Cell.z);

	Vec3 _j = (s - cam.Position) / Dir;

	if (_j.z <= _j.x && _j.z <= _j.y) return Hit(2, _j.z);
	if (_j.x <= _j.y && _j.x <= _j.z) return Hit(0, _j.x);
	if (_j.y <= _j.x && _j.y <= _j.z) return Hit(1, _j.y);
	return Hit((_j.x + _j.y + _j.z) / 3, 0);
}

float subtract_abs(float f1, float f2) restrict(amp,cpu) {
	return f1 > f2 ? f1 - f2 : f2 - f1;
}
Color RenderViewRay(float x, float y, unsigned int i, array_view<Color, 1> _automataGrid, Camera cam, unsigned int _aw, unsigned int _ah, unsigned int _al) restrict(amp, cpu) {
	Vec3 dir(x, y, 1);
	dir = cam.RotateDirection(dir);

	Vec3 Cell = cam.Position;
	Color c;

	Hit hit = DetermineNextHop(dir, Cell, cam);

	for (int k = 0; k < maxView; k++) {
		Cell = (dir * (hit.j + 0.01f)) + cam.Position;

		if (Cell.x < 0 || Cell.x > _aw) {
			if (subtract_abs(Cell.z,roundf(Cell.z)) < 0.05f) return Color(0, 0, UINT_MAX);
			else return Color();
		}

		if (Cell.y < 0 || Cell.y>_ah) {
			if (subtract_abs(Cell.z,roundf(Cell.z)) < 0.05f) return Color(0, UINT_MAX, 0);
			else return Color();
		}

		if (Cell.z < 0 || Cell.z>_al) {
			if (subtract_abs(Cell.y,roundf(Cell.y)) < 0.05f) return Color(UINT_MAX, 0, 0);
			else return Color();
		}

		int indx = floorf(Cell.x) + ((floorf(Cell.y) + (floorf(Cell.z) * _ah)) * _aw);

		c = _automataGrid[indx];

		if (!c.IsBlack()) {
			return c;
		}

		hit = DetermineNextHop(dir, Cell, cam);
	}
	return Color(0, 0, 0);
}

completion_future RenderFrame() {
	const float step_x = 2.0f / w;
	const float step_y = 2.0f / h;
	unsigned int i = 0;

	Camera cam = *camera;
	float _w = w, _h = h;

	const unsigned int _aw = automota->w, _ah = automota->h, _al = automota->l;

	array_view<Color, 2> _Frame(h, w, Frame);
	array_view<Color, 1> _automataGrid(automota->w * automota->h * automota->l, automota->Grid);

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

	/*for (int x = 0, y = 0; y < h;) {
		float vx = (y * step_x) - 1;
		float vy = (x * step_y) - 1;

		vx *= cam.fov;
		vy *= cam.fov * (_h / _w);

		_Frame[y][x] = RenderViewRay(vx, vy, i, _automataGrid, cam, _aw, _ah, _al);

		x++;
		if (x == w) { x = 0; y++; }
	}*/

	return _Frame.synchronize_async();
}

void OntoConsole() {
	for (unsigned int x = 0, y = 0; y < h;) {
		if (Frame[x + (y * w)].IsBlack()) std::cout << '1';
		else std::cout << '0';
		x++;
		if (x == w) { x = 0; y++; std::cout << '\n'; }
	}
}
