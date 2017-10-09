#include "Buffer.h"

void Buffer::ConvertFloatToInt(const FBufferMono& Origin, IBufferMono& Target)
{
	Target.clear();
	int FSize = Origin.size();
	for (int i = 0; i < FSize; i++)
		Target.push_back(Complex<short>(
			Origin[i].Re * float(SHRT_MAX),
			Origin[i].Im * float(SHRT_MAX)
			));
}

void Buffer::ConvertIntToFloat(const IBufferMono& Origin, FBufferMono& Target)
{
	Target.clear();
	int FSize = Origin.size();
	for (int i = 0; i < FSize; i++)
		Target.push_back(Complex<float>(
			float(Origin[i].Re) / float(SHRT_MAX),
			float(Origin[i].Im) / float(SHRT_MAX)
			));
}