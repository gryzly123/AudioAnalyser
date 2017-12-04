#pragma once
#include <string>

public ref struct RackItemContents
{
	System::String^ CurrentPluginName = gcnew System::String(L"(none)");
	float DryWetMix = 1.0f;
	bool HasConfigWindow = false;
	bool HasVisWindow = false;
	bool IsBypassed = false;
	bool IsNullPlugin = true;
};