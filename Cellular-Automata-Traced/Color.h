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

	Color operator+(Color V)restrict(amp, cpu)
	{
		Color N(R + V.R, G + V.G, B + V.B);
		return N;
	}

	void operator+=(Color V) restrict(amp, cpu)
	{
		R += V.R;
		G += V.G;
		B += V.B;
	}

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
