#pragma once
class AutomotaGrid
{
private:
	bool *Grid;

	void InitGrid() {
		Grid = new bool[h * w * l];

		for (unsigned int i = 0; i < h * w * l; i++) Grid[i] = false;
	}

public:
	unsigned int w = 10, h = 10, l = 10;

	AutomotaGrid() {
		this->InitGrid();
	}

	AutomotaGrid(unsigned int w, unsigned int h, unsigned int l) {
		this->h = h;
		this->w = w;
		this->l = l;
		this->InitGrid();
	}

	bool* GetCellNeighbours(unsigned int x, unsigned int y, unsigned int z) {
		bool* cells = new bool[9];
		char i = 0;

		for (int _x = x - 1, _y = y - 1, _z = z - 1; _z <= z + 1; i++) {

			if (_x >= 0 && _y >= 0 && _z >= 0 && _x <= w && _y <= h && _z <= l) 
				cells[i] = Grid[_x + (_y * w) + (_z * h * w)];

			_x++;
			if (_x > x + 1) { _x = x - 1; _y++; }
			if (_y > y + 1) { _y = y - 1; _z++; }
		}

		return cells;
	}
};

