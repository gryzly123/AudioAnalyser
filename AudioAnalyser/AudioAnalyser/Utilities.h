#pragma once
#include "PCH.h"
#define ComplexF std::complex<float>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;
template<class A>
public ref class MonitoredArray
{
public:
	List<A>^ Array;
	MonitoredArray() { Array = gcnew List<A>(); }
	inline Void Lock() { Monitor::Enter(this); }
	inline Void Unlock() { Monitor::Exit(this); }
	inline Int32 Size() { return Array->Count; }
	inline Void Empty() { return Array->Clear(); }
	inline Void PushLast(const A& Element) { Array->Add(Element); }
	inline Void PushFirst(const A& Element) { Array->Insert(0, Element); }
	inline Void PopFirst() { Array->RemoveAt(0); }
	inline A operator[](int Index) { return Array[Index]; }
	inline A Get(int Index) { return Array[Index]; }
};

namespace Utilities
{
	//konwersje string�w
	std::wstring    WideFromString(const std::string In);
	std::wstring    WideFromAsciiCharArray(const char* In);
	std::wstring    WideFromMultibyteCharArray(const char* In);
	std::string     MultibyteCharFromWide(std::wstring In);
	std::wstring    WideFromSystemString(System::String^ In);
	System::String^ SystemStringFromWide(const std::wstring In);

	//messageboxy
	void ShowMessagebox(std::wstring Message, std::wstring WindowName = L"Alert");
	void ShowMessageboxDebugonly(std::wstring Message, std::wstring WindowName = L"Debug window");

	//funkcje matematyczne
	template<typename T>
	inline const T Clamp(const T& Val, const T& Min, const T& Max) { return (Val < Min) ? Min : ((Val > Max) ? Max : Val); }

	template<typename T>
	inline void Swap(T& A, T& B) { T Helper = A; A = B; B = Helper; }
	
	template<typename T>
	inline const T WeightedAvg(const T& A, const T& B, float W) { return (A * (1.0f - W)) + (B * W); }

	void LinearInterpolateArrays(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, int OutLength);
	
	//szybka transformata Fouriera - Cooley-Tukey
	void Fft(ComplexF* In, int Length);
	void FftRegroup(ComplexF* In, int Length);
	void FftProcessResult(ComplexF* In, int Length);
}
