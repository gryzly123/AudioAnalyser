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

//w zwi�zku z tym, �e bufory nie s� same w sobie klas�, dzia�ania na nich
//umieszczone s� nie w klasie, lecz przestrzeni nazw.
//funkcje korzystaj� z szablonu "UBuffer", �eby zachowa� kompatybilno��
//obu typ�w (float i short). U oznacza tu 'undefined'.
namespace Buffer
{
	void ConvertFloatToInt(const FBufferMono& Origin, IBufferMono& Target);
	void ConvertIntToFloat(const IBufferMono& Origin, FBufferMono& Target);

};