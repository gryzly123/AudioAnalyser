#pragma once
#include <vector>

template<typename A>
struct Complex
{
	A Re;			//liczba rzeczywista
	A Im;			//liczba urojona

	//konstruktory
	Complex() { Re = 0; Im = 0; }
	Complex(A r, A i) { Re = r; Im = i; }
	~Complex() { }

	//operacje na jednej liczbie
	inline A Magnitude();
	static Complex<A> Exp(A Im);
	Complex<A>& operator=(Complex<A>& Other);
};

//wypisywanie do konsoli i pliku
template<typename A>
std::ostream& operator<<(std::ostream& stream, const Complex<A>& c);

//operacje na dwóch liczbach
template<typename T>
Complex<T>& operator+(Complex<T>&A, Complex<T>& B);

template<typename T>
Complex<T>& operator-(Complex<T>&A, Complex<T>& B);

template<typename T>
Complex<T>& operator*(Complex<T>&A, Complex<T>& B);
