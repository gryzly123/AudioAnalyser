#pragma once
#include "ComplexNumbers.h"

typedef std::vector<Complex<float>> FBufferMono;
typedef std::vector<Complex<short>> IBufferMono;

struct FBufferStereo
{
	FBufferMono L;
	FBufferMono R;
};

struct IBufferStereo
{
	IBufferMono L;
	IBufferMono R;
};

//w zwi¹zku z tym, ¿e bufory nie s¹ same w sobie klas¹, dzia³ania na nich
//umieszczone s¹ nie w klasie, lecz przestrzeni nazw.
//funkcje korzystaj¹ z szablonu "UBuffer", ¿eby zachowaæ kompatybilnoœæ
//obu typów (float i short). U oznacza tu 'undefined'.
namespace Buffer
{
	void ConvertFloatToInt(const FBufferMono& Origin, IBufferMono& Target);
	void ConvertIntToFloat(const IBufferMono& Origin, FBufferMono& Target);

};