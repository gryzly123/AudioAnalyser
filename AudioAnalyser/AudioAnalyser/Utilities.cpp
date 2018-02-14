#include "PCH.h"
#include <msclr\marshal.h>

#pragma managed(push, off)
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

std::string Utilities::MultibyteCharFromWide(std::wstring In)
{
	char* TargetStr = new char[MAX_SIZE];
	WideCharToMultiByte(CP_UTF8, 0, In.c_str(), -1, TargetStr, MAX_SIZE, NULL, NULL);
	std::string Result = TargetStr;
	delete TargetStr;
	return Result;
}

#undef MAX_SIZE
#pragma managed(push, on)
std::wstring Utilities::WideFromSystemString(System::String^ In)
{
	return msclr::interop::marshal_as<std::wstring>(In);
}

System::String^ Utilities::SystemStringFromWide(const std::wstring In)
{
	return gcnew System::String(In.c_str());
}

void Utilities::ShowMessagebox(std::wstring Message, std::wstring WindowName)
{
	System::String^ Msg = gcnew System::String(Message.c_str());
	System::String^ Window = gcnew System::String(WindowName.c_str());
	System::Windows::Forms::MessageBox::Show(Msg, Window);
}

void Utilities::ShowMessagebox(System::String^ Message, System::String^ WindowName)
{
	System::Windows::Forms::MessageBox::Show(Message, WindowName);
}

void Utilities::LinearInterpolate(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, int OutLength)
{
	Out->Empty();
	int InSize = In->Size();
	int OutSize = OutLength;

	if (InSize == 0)
	{
		for (int i = 0; i < OutSize; ++i) Out->PushLast(0);
		return;
	}

	for (int i = 0; i < OutSize; ++i)
	{
		float Pt = (float)i / (float)OutSize;
		Pt *= (float)InSize;

		int FirstIndex = (int)Pt;
		int SecondIndex = FirstIndex + 1;
		float InterVal = Pt - (float)FirstIndex;
		if (FirstIndex + 2 >= InSize) { FirstIndex = InSize - 1; SecondIndex = FirstIndex; }
		float NewVal = WeightedAvg(In[FirstIndex], In[SecondIndex], InterVal);
		Out->PushLast(NewVal);
	}
}

void Utilities::CutAndInterpolateSubrange(MonitoredArray<float>^ In, MonitoredArray<float>^ Out, float From, float To, int OutLength)
{
	int CutFromStart = (int)(From * (float)In->Size());
	int CutFromEnd = (int)((float)In->Size() - To * (float)In->Size());
	while (--CutFromStart >= 0) In->PopFirst();
	while (--CutFromEnd >= 0) In->PopLast();
	LinearInterpolate(In, Out, OutLength);
}

#pragma managed(push, off)
void Utilities::Fft(ComplexF* In, int Length)
{
	if (Length == 1) return;

	FftRegroup(In, Length);
	int lh = Length / 2;
	Fft(In, lh);
	Fft(In + lh, lh);

	int Cond = Length / 2;
	for (int i = 0; i < Cond; ++i)
	{
		ComplexF Even = In[i];
		ComplexF Odd = In[i + Length / 2];
		ComplexF exp = std::exp(ComplexF(0.0f, -2.0f * 3.141592f * (float)i / (float)Length));
		In[i] = Even + (exp * Odd);
		In[i + Length / 2] = Even - (exp * Odd);
	}
}

void Utilities::FftRegroup(ComplexF* In, int Length)
{
	int HalfLen = Length / 2;
	int Seek = HalfLen;
	ComplexF* Helper = new ComplexF[Length / 2];
	for (int i = 0; i < Length; i += 2) Helper[i / 2] = In[i]; //nieparzyste do pomocniczej
	for (int i = 0; i < HalfLen; ++i) In[i] = In[i * 2 + 1];   //parzyste do pierwszej po³owy
	for (int i = 0; i < HalfLen; ++i) In[Seek++] = Helper[i];  //nieparzyste do drugiej po³owy
	delete[] Helper;
}

#pragma managed(push, on)
MonitoredArray<float>^ Utilities::FftProcessResult(ComplexF* In, int Length)
{
	MonitoredArray<float>^ Result = gcnew MonitoredArray<float>();

	int HalfLen = Length / 2;
	for (int i = 0; i < HalfLen; ++i) Result->PushLast(std::sqrt((In[i].real() * In[i].real()) + (In[i].imag() * In[i].imag())) / (float)HalfLen);
	return Result;
}
