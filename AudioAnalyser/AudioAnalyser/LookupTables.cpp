#include "PCH.h"
#include "LookupTables.h"

//Precomputed Sin

PrecomputedSin::PrecomputedSin(int Precision) : Precision(Precision)
{
	SinArray = new float[Precision];
	for (int i = 0; i < Precision; ++i) SinArray[i] = sin(2.0f * M_PI * (float)i / (float)Precision);
}

PrecomputedSin::~PrecomputedSin()
{
	delete[] SinArray;
}

float PrecomputedSin::Get(float x)
{
	x -= floorf(x);
	int Index = x * Precision / ( 2.0f * M_PI);
	Index %= Precision;
	return SinArray[Index];
}
