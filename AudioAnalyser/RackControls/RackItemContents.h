#pragma once
#include <string>

ref struct RackItemContents
{
	System::String^ CurrentPluginName = gcnew System::String(L"(none)");
	bool HasConfigWindow = false;
	bool HasVisWindow = false;
	bool IsBypassed = false;
};