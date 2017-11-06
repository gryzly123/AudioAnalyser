#pragma once
#include "PCH.h"

namespace Utilities
{
	std::wstring WideFromString(const std::string In);
	std::wstring WideFromAsciiCharArray(const char* In);
	std::wstring WideFromMultibyteCharArray(const char* In);
	std::wstring WideFromSystemString(System::String^ In);
	void ShowMessagebox(std::wstring Message, std::wstring WindowName = L"Alert");
	void ShowMessageboxDebugonly(std::wstring Message, std::wstring WindowName = L"Debug window");

	template<typename T>
	inline const T& Clamp(const T& Val, const T& Min, const T& Max) { return (Val < Min) ? Min : ((Val > Max) ? Max : Val); }

	template<typename T>
	inline void Swap(T& A, T& B) { T& Helper = A; A = B; B = Helper; }

}