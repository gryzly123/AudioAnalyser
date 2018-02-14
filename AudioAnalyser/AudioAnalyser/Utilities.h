#pragma once
#include "PCH.h"
#define ComplexF std::complex<float>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;

//lista dwukierunkowa z obs³ug¹ CLRowych mutexów (Monitor)
template<class A>
public ref class MonitoredArray
{
public:
	std::deque<A>* Array;
	MonitoredArray() { Array = new std::deque<A>(); }
	~MonitoredArray() { Empty(); delete Array; }
	inline Void Lock() { Monitor::Enter(this); }
	inline Void Unlock() { Monitor::Exit(this); }
	inline Int32 Size() { return Array->size(); }
	inline Void Empty() { return Array->clear(); }
	inline Void PushLast(const A& Element) { Array->push_back(Element); }
	inline Void PushFirst(const A& Element) { Array->push_front(Element); }
	inline Void PopFirst() { Array->pop_front(); }
	inline Void PopLast() { Array->pop_back(); }
	inline A operator[](int Index) { return  Array->operator[](Index); }
	inline A Get(int Index) { return Array->operator[](Index); }
	inline std::deque<A>* GetRawArrayUnsafe() { return Array; }
};

namespace Utilities
{
	//konwersje stringów
	std::wstring    WideFromString(const std::string In);
	std::wstring    WideFromAsciiCharArray(const char* In);
	std::wstring    WideFromMultibyteCharArray(const char* In);
	std::string     MultibyteCharFromWide(std::wstring In);
	std::wstring    WideFromSystemString(System::String^ In);
	System::String^ SystemStringFromWide(const std::wstring In);

	//messageboxy
	void ShowMessagebox(std::wstring Message, std::wstring WindowName = L"Alert");
	void ShowMessagebox(System::String^ Message, System::String^ WindowName = L"Alert");

	//clamp
	template<typename T>
	inline const T Clamp(const T& Val, const T& Min, const T& Max) { return (Val < Min) ? Min : ((Val > Max) ? Max : Val); }

	//zamiana zmiennych
	template<typename T>
	inline void Swap(T& A, T& B) { T Helper = A; A = B; B = Helper; }
	
	//œrednia wa¿ona
	template<typename T>
	inline const T WeightedAvg(const T& A, const T& B, float W) { return (A * (1.0f - W)) + (B * W); }

	//interpolacja liniowa
	void LinearInterpolate(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, int OutLength);
	void CutAndInterpolateSubrange(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, float From, float To, int OutLength);
	
	//szybka transformata Fouriera - Cooley-Tukey
	void Fft(ComplexF* In, int Length);                 
	
	//rearan¿acja elementów do FFT
	void FftRegroup(ComplexF* In, int Length);
	
    //konwersja wyniku FFT na zrozumia³y dla cz³owieka
	MonitoredArray<float>^ FftProcessResult(ComplexF* In, int Length);
}
