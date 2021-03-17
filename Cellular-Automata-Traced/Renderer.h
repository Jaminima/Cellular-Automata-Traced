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
const unsigned int maxView = 100;
Color* Frame;

template <typename T> int sgn(T val) restrict(amp,cpu) {
	return (T(0) < val) - (val < T(0));
}

void Setup(AutomotaGrid* _automata, Camera* _camera) {
	automota = _automata;
	camera = _camera;

	camera->Position = Vec3(_automata->w / 2, _automata->h / 2, _automata->l / 2);
	Frame = new Color[w * h];
}

struct Hit {
public:
	int axis = 0;
	float j = 0;

	Hit() restrict(amp,cpu){}
};

Hit DetermineNextHop(Vec3 Dir, Vec3 Cell, Camera cam,float lastj) restrict(amp, cpu) {
	Vec3 s = Vec3();

	Cell += (Dir*0.01f);

	if (Dir.x > 0) s.x = ceilf(Cell.x);
	else s.x = floorf(Cell.x);

	if (Dir.y > 0) s.y = ceilf(Cell.y);
	else s.y = floorf(Cell.y);

	if (Dir.z > 0) s.z = ceilf(Cell.z);
	else s.z = floorf(Cell.z);

	Vec3 _j = (s - cam.Position) / Dir;

	for (int i = 0; i < 3; i++) {
		if (_j.Data[i] > lastj) {
			float next = _j.Data[(i + 1) % 3];
			float nextnext = _j.Data[(i + 2) % 3];
			if ((next <= lastj || next > _j.Data[i]) && (nextnext <= lastj || nextnext > _j.Data[i])) {
				Hit hit;
				hit.axis = i;
				hit.j = _j.Data[i];
				return hit;
			}
		}
	}
	return Hit();
}

Color RenderViewRay(float x, float y, unsigned int i, array_view<Color, 1> _automataGrid, Camera cam, unsigned int _aw, unsigned int _ah, unsigned int _al) restrict(amp, cpu) {
	Vec3 dir(x, y, 1);
	dir = cam.RotateDirection(dir);

	Vec3 Cell = cam.Position + dir;

	Hit hit = DetermineNextHop(dir, Cell, cam, 0);

	for (int k = 0; k < maxView; k++) {
		Cell = (dir * (hit.j+0.01f)) + cam.Position;

		int indx = floorf(Cell.x) + (floorf(Cell.y) * _aw) + (floorf(Cell.z) * _aw * _ah);

		if (!_automataGrid[indx].IsBlack()) {
			return _automataGrid[indx];
		}

		hit = DetermineNextHop(dir, Cell, cam, hit.j);
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
