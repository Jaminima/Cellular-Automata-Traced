#pragma once
class Color
{
public:
	unsigned int R, G, B, A;

	Color() {
		R = 0;
		G = 0;
		B = 0;
		A = UINT_MAX;
	};

	Color(unsigned int R, unsigned int G, unsigned int B) {
		this->R = R;
		this->G = G;
		this->B = B;
		A = UINT_MAX;
	}

	bool IsBlack() {
		return R == 0 && G == 0 && B == 0;
	}
};
