#include "Utilities.h"

std::wstring Utilities::WideFromString(const std::string In)
{
	return std::wstring(In.begin(), In.end());
}

std::wstring Utilities::WideFromCharArray(const char* In)
{
	return Utilities::WideFromString(std::string(In));
}
