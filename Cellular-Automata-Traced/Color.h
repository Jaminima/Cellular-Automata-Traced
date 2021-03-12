#pragma once
class Color
{
public:
	unsigned int R, G, B, A;

	Color() restrict(amp, cpu) {
		R = 0;
		G = 0;
		B = 0;
		A = UINT_MAX;
	};

	Color(unsigned int R, unsigned int G, unsigned int B) restrict(amp, cpu) {
		this->R = R;
		this->G = G;
		this->B = B;
		A = UINT_MAX;
	}

	bool IsBlack() restrict(amp, cpu) {
		return R == 0 && G == 0 && B == 0;
	}
};
