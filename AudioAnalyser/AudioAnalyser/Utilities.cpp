#include "Utilities.h"
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

std::wstring Utilities::WideFromString(const std::string In)
{
	return std::wstring(In.begin(), In.end());
}

std::wstring Utilities::WideFromAsciiCharArray(const char* In)
{
	return Utilities::WideFromString(std::string(In));
}

#define MAX_SIZE 4096

std::wstring Utilities::WideFromMultibyteCharArray(const char* In)
{
	wchar_t* TargetStr = new wchar_t[MAX_SIZE];
	MultiByteToWideChar(CP_UTF8, 0, In, -1, TargetStr, MAX_SIZE);
	std::wstring Result = TargetStr;
	delete[] TargetStr;
	return Result;
}

#undef MAX_SIZE

std::wstring Utilities::WideFromSystemString(System::String^ In)
{
	return msclr::interop::marshal_as<std::wstring>(In);
}


void Utilities::ShowMessagebox(std::wstring Message, std::wstring WindowName)
{
	System::String^ Msg = gcnew System::String(Message.c_str());
	System::String^ Window = gcnew System::String(WindowName.c_str());
	System::Windows::Forms::MessageBox::Show(Msg, Window);
}

void Utilities::ShowMessageboxDebugonly(std::wstring Message, std::wstring WindowName)
{
	ShowMessagebox(Message, WindowName);
}
