#pragma once
#include <string>

public ref struct RackItemContents
{
	System::String^ CurrentPluginName = gcnew System::String(L"(none)");
	bool HasConfigWindow = false;
	bool HasVisWindow = false;
	bool IsBypassed = false;
	bool IsNullPlugin = true;
};