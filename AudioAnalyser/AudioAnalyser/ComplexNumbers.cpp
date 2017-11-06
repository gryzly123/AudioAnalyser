#include "PCH.h"
#include "ComplexNumbers.h"

template<typename A>
inline A Complex<A>::Magnitude()
{
	return sqrt((Re*Re) + (Im*Im));
}

template<typename A>
Complex<A> Complex<A>::Exp(A Im)
{
	std::complex<A> a = std::polar(1.0f, Im);
	return Complex<A>(a.real(), a.imag());
	//return Complex(cosf(Im), sinf(Im));
}

template<typename A>
Complex<A>& Complex<A>::operator=(Complex<A>& Other)
{
	return Complex<A>(Other.Re, Other.Im);
}

template<typename A>
std::ostream& operator<<(std::ostream& stream, const Complex<A>& c)
{
	if (c.Im < 0)
	{
		stream << c.Re << " - " << -c.Im << "i";
	}
	else
	{
		stream << c.Re << " + " << c.Im << "i";
	}

	return stream;
}

template<typename T>
Complex<T>& operator+(Complex<T>&A, Complex<T>& B)
{
	return Complex<T>(A.Re + B.Re, A.Im + B.Im);
}

template<typename T>
Complex<T>& operator-(Complex<T>&A, Complex<T>& B)
{
	return Complex<T>(A.Re - B.Re, A.Im - B.Im);
}

template<typename T>
Complex<T>& operator*(Complex<T>&A, Complex<T>& B)
{
	return Complex<T>((A.Re * B.Re) - (A.Im * B.Im), (A.Re * B.Im) + (A.Im * B.Re));
}