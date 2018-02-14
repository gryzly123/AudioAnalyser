#include "PCH.h"
#include "LookupTables.h"

//Precomputed Sin

PrecomputedSin::PrecomputedSin(int Precision) : Precision(Precision)
{
	SinArray = new float[Precision];
	for (int i = 0; i < Precision; ++i) SinArray[i] = sin(M_TAU * (float)i / (float)Precision);
}

PrecomputedSin::~PrecomputedSin()
{
	delete[] SinArray;
}

float PrecomputedSin::Get(float x)
{
	x /= M_TAU;
	x -= floorf(x);
	int Index = (int)(x * Precision);
	Index %= Precision;
	return SinArray[Index];
}

float PrecomputedSin::GetWithTau(float x)
{
	x -= floorf(x);
	int Index = (int)(x * Precision);
	Index %= Precision;
	return SinArray[Index];
}
