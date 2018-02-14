#pragma once

//lookup dla sinusa - znacz�co optymalizuje z�o�ono�� arytmetyki dla
//wzor�w korzystaj�cych z sinusa kosztem pami�ci i dok�adno�ci
class PrecomputedSin
{
private:
	const int Precision;
	float* SinArray;

public:
	PrecomputedSin(int Precision);
	~PrecomputedSin();

	//warto�� sin(x)
	float Get(float x);

	//warto�� sin(2*pi*x)
	float GetWithTau(float x);
};
