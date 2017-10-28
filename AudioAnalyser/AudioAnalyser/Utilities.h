#pragma once
#include <string>

namespace Utilities
{
	std::wstring WideFromString(const std::string In);
	std::wstring WideFromAsciiCharArray(const char* In);
	std::wstring WideFromMultibyteCharArray(const char* In);
	std::wstring WideFromSystemString(System::String^ In);
	void ShowMessagebox(std::wstring Message, std::wstring WindowName = L"Alert");
	void ShowMessageboxDebugonly(std::wstring Message, std::wstring WindowName = L"Debug window");
}