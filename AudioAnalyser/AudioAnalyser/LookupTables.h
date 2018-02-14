#pragma once

//lookup dla sinusa - znacz¹co optymalizuje z³o¿onoœæ arytmetyki dla
//wzorów korzystaj¹cych z sinusa kosztem pamiêci i dok³adnoœci
class PrecomputedSin
{
private:
	const int Precision;
	float* SinArray;

public:
	PrecomputedSin(int Precision);
	~PrecomputedSin();

	//wartoœæ sin(x)
	float Get(float x);

	//wartoœæ sin(2*pi*x)
	float GetWithTau(float x);
};
