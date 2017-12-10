#pragma once

class PrecomputedSin
{
private:
	const int Precision;
	float* SinArray;

public:
	PrecomputedSin(int Precision);
	~PrecomputedSin();
	float Get(float x);
	float GetWithTau(float x);
};
