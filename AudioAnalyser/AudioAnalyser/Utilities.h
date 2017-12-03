#pragma once
#include "PCH.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;
template<class A>
public ref class MonitoredArray
{
public:
	List<A>^ Array;
	MonitoredArray() { Array = gcnew List<A>(); }
	Void Lock() { Monitor::Enter(this); }
	Void Unlock() { Monitor::Exit(this); }
	Int32 Size() { return Array->Count; }
	Void PushLast(const A& Element) { Array->Add(Element); }
	Void PushFirst(const A& Element) { Array->Insert(0, Element); }
	Void PopFirst() { Array->RemoveAt(0); }
	A operator[](int Index) { return Array[Index]; }
};

namespace Utilities
{
	std::wstring WideFromString(const std::string In);
	std::wstring WideFromAsciiCharArray(const char* In);
	std::wstring WideFromMultibyteCharArray(const char* In);
	std::string  MultibyteCharFromWide(std::wstring In);
	std::wstring WideFromSystemString(System::String^ In);
	void ShowMessagebox(std::wstring Message, std::wstring WindowName = L"Alert");
	void ShowMessageboxDebugonly(std::wstring Message, std::wstring WindowName = L"Debug window");

	template<typename T>
	inline const T& Clamp(const T& Val, const T& Min, const T& Max) { return (Val < Min) ? Min : ((Val > Max) ? Max : Val); }

	template<typename T>
	inline void Swap(T& A, T& B) { T Helper = A; A = B; B = Helper; }

	void LinearInterpolateArrays(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, int OutLength);
}
