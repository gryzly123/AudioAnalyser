#pragma once
#include "PCH.h"
#include "DspPluginParameter.h"
#include "DynamicPluginVizWindow.h"

using namespace AudioAnalyser;
using namespace System;

typedef DspPluginParameter Param;
#define Val CurrentValue

class DspPlugin
{
protected:
	std::vector<DspPluginParameter*> ParameterRefsForUi;
	DspPlugin(const std::wstring PluginName, const bool HasVisualization = false)
		: PluginName(PluginName),
		HasVisualization(HasVisualization) { }

public:
	const std::wstring PluginName;
	bool Bypass = false;
	float DryWetMix = 1.0f;
	const bool HasVisualization = false;

	std::vector<DspPluginParameter*> GetParameters() { return ParameterRefsForUi; }
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) = 0;
	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, int Width, int Height, bool FirstFrame) { }
};

class NullPlugin : public DspPlugin
{
public:
	NullPlugin() : DspPlugin(L"(none)") { }
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override { }
};

#ifndef FROM_RACK_CONTROLS
#include "DynamicPluginVizWindow.h"
#define HAS_VIZ true

class SineWaveGenerator : public DspPlugin
{
private:
	float SineStatus = 0;
	float SineInc = 0;

	Param SineAmp = Param(PT_Float, L"Sine volume", 0.0f, 1.0f, 0.6f);
	Param SineFrequency = Param(PT_Float, L"Sine frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 1.0f);

public:
	SineWaveGenerator() : DspPlugin(L"Sine Wave")
	{
		SineAmp.FloatValueStep = 0.01f;
		SineFrequency.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&SineAmp);
		ParameterRefsForUi.push_back(&SineFrequency);
		ParameterRefsForUi.push_back(&InvertPhase);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		SineInc = SineFrequency.Val / 44100.f;

		for (int i = 0; i < Length; i++)
		{
			SineStatus += SineInc;
			if (SineStatus > 1) SineStatus -= 1;
			float Value = SineAmp.Val * sin(SineStatus * 2 * M_PI);
			BufferL[i] = Value;
			BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * Value : Value;
		}
	}
};
class SawWaveGenerator : public DspPlugin
{
private:
	float TimeStatus = 0.0f;
	float TimeIncrementation = 0.0f;
	float TempValue = 0.0f;

	Param Amp = Param(PT_Float, L"Saw volume", 0.0f, 1.0f, 0.6f);
	Param Frequency = Param(PT_Float, L"Saw frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 1.0f);
	Param UseEquation = Param(PT_Boolean, L"Use additive synthesis", 0.0f, 1.0f, 0.0f);
	Param EquationN = Param(PT_Float, L"Additive sine count", 1.0f, 100.0f, 30.0f);

public:
	SawWaveGenerator() : DspPlugin(L"Saw Wave")
	{
		Amp.FloatValueStep = 0.01f;
		Frequency.FloatValueStep = 1.0f;
		EquationN.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&Amp);
		ParameterRefsForUi.push_back(&Frequency);
		ParameterRefsForUi.push_back(&InvertPhase);
		ParameterRefsForUi.push_back(&UseEquation);
		ParameterRefsForUi.push_back(&EquationN);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		TimeIncrementation = Frequency.Val / AUDIO_SAMPLERATE;

		for (int i = 0; i < Length; ++i)
		{
			TimeStatus += TimeIncrementation;
			if (TimeStatus > 1.0f) TimeStatus -= 1.0f;

			if (UseEquation.Val > 0.0f)
			{
				TempValue = 0.0f;
				for (int k = 1; k <= EquationN.Val; ++k)
				{
					float T = sin(2.0f * M_PI * (float)k * TimeStatus) / (float)k;
					if (k % 2 != 0) T *= -1.0f;
					TempValue += T;
				}
				TempValue = (TempValue * 2.0f * Amp.Val / M_PI);
			}
			else TempValue = Amp.Val * (TimeStatus * 2.0f - 1.0f);

			BufferL[i] = TempValue;
			BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
		}
	}
};
class SquareWaveGenerator : public DspPlugin
{
private:
	float TimeStatus = 0.0f;
	float TimeIncrementation = 0.0f;
	float TempValue = 0.0f;

	Param Amp = Param(PT_Float, L"Saw volume", 0.0f, 1.0f, 0.6f);
	Param Frequency = Param(PT_Float, L"Saw frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 1.0f);
	Param UseEquation = Param(PT_Boolean, L"Use additive synthesis", 0.0f, 1.0f, 0.0f);
	Param EquationN = Param(PT_Float, L"Additive sine count", 1.0f, 100.0f, 30.0f);

public:
	SquareWaveGenerator() : DspPlugin(L"Square Wave")
	{
		Amp.FloatValueStep = 0.01f;
		Frequency.FloatValueStep = 1.0f;
		EquationN.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&Amp);
		ParameterRefsForUi.push_back(&Frequency);
		ParameterRefsForUi.push_back(&InvertPhase);
		ParameterRefsForUi.push_back(&UseEquation);
		ParameterRefsForUi.push_back(&EquationN);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		TimeIncrementation = Frequency.Val / AUDIO_SAMPLERATE;

		for (int i = 0; i < Length; ++i)
		{
			TimeStatus += TimeIncrementation;
			if (TimeStatus > 1.0f) TimeStatus -= 1.0f;

			if (UseEquation.Val > 0.0f)
			{
				TempValue = 0.0f;
				int DoubleN = EquationN.Val * 2;
				for (int x = 1; x <= DoubleN; x += 2)
				{
					// x = (2k - 1)
					TempValue += sin(2.0f * M_PI * (float)x * TimeStatus) / (float)x;
				}
				TempValue = (TempValue * 4.0f * Amp.Val / M_PI);
			}
			else TempValue = Amp.Val * (TimeStatus >= 0.5f ? 1.0f : -1.0f);

			BufferL[i] = TempValue;
			BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
		}
	}
};
class WhiteNoiseGenerator : public DspPlugin
{
private:
	Param Amp = Param(PT_Float, L"Noise volume", 0.0f, 1.0f, 0.2f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 1.0f);
	Param EquationN = Param(PT_Float, L"Random() count", 1.0f, 12.0f, 4.0f);
	gcroot<Random^> RNG;
	float TempValue = 0.0f;

public:
	WhiteNoiseGenerator() : DspPlugin(L"White Noise")
	{
		Amp.FloatValueStep = 0.01f;
		EquationN.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&Amp);
		ParameterRefsForUi.push_back(&InvertPhase);
		ParameterRefsForUi.push_back(&EquationN);
		RNG = gcroot<Random^>(gcnew Random());
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; ++i)
		{
			for (int x = 0; x < EquationN.Val; ++x) TempValue += RNG->NextDouble();
			TempValue /= EquationN.Val;
			TempValue -= 0.5f;
			TempValue *= Amp.Val;

			BufferL[i] = TempValue;
			BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
		}
	}
};
class Oscilloscope : public DspPlugin
{
	Param CurveDuration = Param(PT_Float, L"Curve duration [ms]", 1.0f, 200.0f, 20.0f);
	Param Channels = Param(PT_Enum, L"Channels", 2.0f, 3.0f, 1.0f);
	Param ImgPadding = Param(PT_Float, L"Margin [px]", 1.0f, 20.0f, 10.0f);

	gcroot<MonitoredArray<float>^> Data;
	gcroot<MonitoredArray<float>^> Interp;
	gcroot<Pen^>                   DataPencil;
	gcroot<SolidBrush^>            DataBrush;
	gcroot<Pen^>                   HelperPencil1;
	gcroot<Pen^>                   HelperPencil2;

public:
	Oscilloscope() : DspPlugin(L"Oscilloscope", HAS_VIZ)
	{
		std::wstring* ChannelNames = new std::wstring[3];
		ChannelNames[0] = L"Left";
		ChannelNames[1] = L"Right";
		ChannelNames[2] = L"Mixdown";

		Channels.EnumNames = ChannelNames;

		ImgPadding.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&Channels);
		ParameterRefsForUi.push_back(&CurveDuration);
		ParameterRefsForUi.push_back(&ImgPadding);

		Data = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		Interp = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataPencil = gcroot<Pen^>(gcnew Pen(Color::Black, 1));
		DataBrush = gcroot<SolidBrush^>(gcnew SolidBrush(Color::Black));
		HelperPencil1 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
		HelperPencil2 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
		HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int CurvePointsSize = (float)AUDIO_SAMPLERATE * (float)CurveDuration.Val / 1000.0f;

		Data->Lock();
		switch ((int)Channels.Val)
		{
		case 0:
			for (int i = 0; i < Length; ++i) Data->PushLast(BufferL[i]);
			break;
		case 1:
			for (int i = 0; i < Length; ++i) Data->PushLast(BufferR[i]);
			break;
		case 2:
			for (int i = 0; i < Length; ++i) Data->PushLast((BufferL[i] + BufferR[i]) / 2.0f);
			break;
		}
		int ExcessData = Data->Size() - CurvePointsSize;
		while (--ExcessData > 0) Data->PopFirst();
		Data->Unlock();
	}

	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, int Width, int Height, bool FirstFrame) override
	{
		const float Padding = ImgPadding.Val;
		const float HelperLineCount = 10.0f;
		const float WorkAreaHorizontal = Width - (2 * Padding);
		const float WorkAreaVertical = Height - (2 * Padding);
		const int MaxPoints = Width;
		const int Range = Height;

		Image->Clear(Color::White);
		Image->DrawLine(HelperPencil1, Padding, Padding, Padding, Height - Padding);
		Image->DrawLine(HelperPencil1, Padding, Height - Padding, Width - Padding, Height - Padding);

		for (int i = 0; i < HelperLineCount + 1; i++)
		{
			float HorizontalX = Padding + (WorkAreaHorizontal / HelperLineCount) * (float)i;
			float VerticalY = Padding + (WorkAreaVertical / HelperLineCount) * (float)(i - 1);

			Image->DrawLine(HelperPencil2,
				HorizontalX,
				Padding,
				HorizontalX,
				(float)((float)Height - Padding));

			Image->DrawLine(HelperPencil2,
				Padding,
				VerticalY,
				(float)((float)Width - Padding),
				VerticalY);
		}

		Data->Lock();
		Utilities::LinearInterpolateArrays((MonitoredArray<float>^)Data, Interp, WorkAreaHorizontal);
		Data->Unlock();

		int LastVal = Range / 2 + ((Single)WorkAreaVertical / 2.0f * -Utilities::Clamp((Single)Interp->operator[](0), -1.0f, 1.0f));
		for (int i = 1; i < WorkAreaHorizontal; ++i)
		{
			int HorizontalVal = (int)(i + Padding);
			float Vall = Utilities::Clamp((Single)Interp->operator[](i), -1.0f, 1.0f);
			int NewPt = Range / 2 + ((Single)WorkAreaVertical / 2.0f * -Vall);
			if (LastVal != NewPt) LastVal = (NewPt < LastVal) ? LastVal - 1 : LastVal + 1;

			if (LastVal == NewPt) Image->FillRectangle(DataBrush, HorizontalVal, LastVal, 1, 1);
			else                  Image->DrawLine(DataPencil, HorizontalVal, LastVal, HorizontalVal, NewPt);

			LastVal = NewPt;
		}
	}
};
class Spectrum : public DspPlugin
{
	Param CurveDuration = Param(PT_Enum, L"Samples", 0.0f, 6.0f, 1.0f);
	Param Channels = Param(PT_Enum, L"Channels", 2.0f, 3.0f, 1.0f);
	Param ImgPadding = Param(PT_Float, L"Margin [px]", 1.0f, 20.0f, 10.0f);

	gcroot<MonitoredArray<float>^> Data         ;
	gcroot<Pen^>                   DataPencil   ;
	gcroot<SolidBrush^>            DataBrush    ;
	gcroot<Pen^>                   HelperPencil1;
	gcroot<Pen^>                   HelperPencil2;

public:
	Spectrum() : DspPlugin(L"Spectrum", HAS_VIZ)
	{
		std::wstring* SampleCounts = new std::wstring[6];
		SampleCounts[0] = L"128";
		SampleCounts[1] = L"256";
		SampleCounts[2] = L"512";
		SampleCounts[3] = L"1024";
		SampleCounts[4] = L"2048";
		SampleCounts[5] = L"4096";
		CurveDuration.EnumNames = SampleCounts;

		std::wstring* ChannelNames = new std::wstring[3];
		ChannelNames[0] = L"Left";
		ChannelNames[1] = L"Right";
		ChannelNames[2] = L"Mixdown";
		Channels.EnumNames = ChannelNames;

		ImgPadding.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&Channels);
		ParameterRefsForUi.push_back(&CurveDuration);
		ParameterRefsForUi.push_back(&ImgPadding);

		Data          = gcroot<MonitoredArray<float>^> (gcnew MonitoredArray<float>());
		DataPencil    = gcroot<Pen^>                   (gcnew Pen(Color::Black, 1));
		DataBrush     = gcroot<SolidBrush^>            (gcnew SolidBrush(Color::Black));
		HelperPencil1 = gcroot<Pen^>                   (gcnew Pen(Color::Gray, 1));
		HelperPencil2 = gcroot<Pen^>                   (gcnew Pen(Color::Gray, 1));
		HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int CurvePointsSize = std::pow(2, 7 + CurveDuration.Val);

		Data->Lock();
		switch ((int)Channels.Val)
		{
		case 0:
			for (int i = 0; i < Length; ++i) Data->PushLast(BufferL[i]);
			break;
		case 1:
			for (int i = 0; i < Length; ++i) Data->PushLast(BufferR[i]);
			break;
		case 2:
			for (int i = 0; i < Length; ++i) Data->PushLast((BufferL[i] + BufferR[i]) / 2.0f);
			break;
		}
		int ExcessData = Data->Size() - CurvePointsSize;
		while (--ExcessData > 0) Data->PopFirst();
		Data->Unlock();
	}

	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, int Width, int Height, bool FirstFrame) override
	{
		const float Padding = ImgPadding.Val;
		const float HelperLineCount = 10.0f;
		const float WorkAreaHorizontal = Width - (2 * Padding);
		const float WorkAreaVertical = Height - (2 * Padding);
		const int MaxPoints = Width;
		const int Range = Height;
		
		Image->Clear(Color::White);
		Image->DrawLine(HelperPencil1, Padding, Padding, Padding, Height - Padding);
		Image->DrawLine(HelperPencil1, Padding, Height - Padding, Width - Padding, Height - Padding);

		for (int i = 0; i < HelperLineCount + 1; i++)
		{
			float HorizontalX = Padding + (WorkAreaHorizontal / HelperLineCount) * (float)i;
			float VerticalY   = Padding + (WorkAreaVertical   / HelperLineCount) * (float)(i - 1);

			Image->DrawLine(HelperPencil2,
				HorizontalX,
				Padding,
				HorizontalX,
				(float)((float)Height - Padding));

			Image->DrawLine(HelperPencil2,
				Padding,
				VerticalY,
				(float)((float)Width - Padding),
				VerticalY);
		}

		Data->Lock();
		int ArrSize = std::pow(2, 7 + CurveDuration.Val);
		if (Data->Size() < ArrSize)
		{
			Data->Unlock();
			return;
		}

		ComplexF* FftResult = new ComplexF[ArrSize];
		for (int i = 0; i < ArrSize; ++i) FftResult[i] = ComplexF(Data->operator[](i), 0.0f);
		Data->Unlock();

		Utilities::Fft(FftResult, ArrSize);
		Utilities::FftProcessResult(FftResult, ArrSize);

		int LastVal = Range / 2 + ((Single)WorkAreaVertical / 2.0f * - Utilities::Clamp((Single)FftResult[0].real(), -1.0f, 1.0f));
		for (int i = 1; i < ArrSize / 2; ++i)
		{
			int HorizontalVal = (int)(i + Padding);
			float Vall = Utilities::Clamp((Single)FftResult[i].real(), -1.0f, 1.0f);
			int NewPt = Range / 2 + ((Single)WorkAreaVertical / 2.0f * - Vall);
			if(LastVal != NewPt) LastVal = (NewPt < LastVal) ? LastVal - 1 : LastVal + 1; 
			
			if (LastVal == NewPt) Image->FillRectangle(DataBrush, HorizontalVal, LastVal, 1, 1);
			else                  Image->DrawLine(DataPencil, HorizontalVal, LastVal, HorizontalVal, NewPt);

			LastVal = NewPt;
		}
	}
};
class SignalParameters : public DspPlugin
{
	Param CurveDuration = Param(PT_Float, L"Peak duration [ms]", 1.0f, 200.0f, 20.0f);
	Param CurveFalloff = Param(PT_Float, L"Peak falloff [ms]", 1.0f, 200.0f, 20.0f);

	float	PeakL = 0.0f,
			PeakR = 0.0f,
			AvgL = 0.0f,
			AvgR = 0.0f,
			DeviationL = 0.0f,
			DeviationR = 0.0f,
			VisiblePeakL = 0.0f,
			VisiblePeakR = 0.0f,
			VisibleAvgL = 0.0f,
			VisibleAvgR = 0.0f,
			VisibleDeviationL = 0.0f,
			VisibleDeviationR = 0.0f;

	gcroot<MonitoredArray<float>^> DataL;
	gcroot<MonitoredArray<float>^> DataR;
	gcroot<Pen^>                   DataPencil;
	gcroot<Pen^>                   HelperPencil1;
	gcroot<Pen^>                   HelperPencil2;
	gcroot<Font^>                  Text;
	gcroot<StringFormat^>          Format;
	gcroot<Brush^>                 TextColor;
	gcroot<Brush^>                 SignalValue;

public:
	SignalParameters() : DspPlugin(L"Signal Parameters", HAS_VIZ)
	{
		ParameterRefsForUi.push_back(&CurveDuration);
		ParameterRefsForUi.push_back(&CurveFalloff);

		DataL = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataR = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataPencil = gcroot<Pen^>(gcnew Pen(Color::Black, 1));
		HelperPencil1 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
		HelperPencil2 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
		HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;

		Text = gcroot<Font^>(gcnew Font("Microsoft Sans Serif", 8.0f, FontStyle::Regular));
		Format = gcroot<StringFormat^>(gcnew StringFormat());
		TextColor = gcroot<Brush^>(gcnew SolidBrush(Color::Black));
		SignalValue = gcroot<Brush^>(gcnew SolidBrush(Color::Black));
		Format->Alignment = StringAlignment::Center;
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int CurvePointsSize = (float)AUDIO_SAMPLERATE * (float)CurveDuration.Val / 1000.0f;

		for (int i = 0; i < Length; ++i)
		{
			DataL->PushLast(BufferL[i]);
			DataR->PushLast(BufferR[i]);
		}
		
		int ExcessData = DataL->Size() - CurvePointsSize;
		while (--ExcessData > 0) 
		{
			DataL->PopFirst();
			DataR->PopFirst();
		}

		PeakL = 0.0f;
		PeakR = 0.0f;
		AvgL = 0.0f;
		AvgR = 0.0f;
		DeviationL = 0.0f;
		DeviationR = 0.0f;

		int Size = DataL->Size();
		for (int i = 0; i < Size; ++i)
		{
			float L = DataL->Get(i), R = DataR->Get(i);
			if (L > PeakL) PeakL = L;
			if (R > PeakR) PeakR = R;
			AvgL += L;
			AvgR += R;
		}

		AvgL /= (float)Size;
		AvgR /= (float)Size;

		for (int i = 0; i < Size; ++i)
		{
			float L = DataL->Get(i), R = DataR->Get(i);
			DeviationL += L - AvgL;
			DeviationR += R - AvgR;
		}

		DeviationL /= (float)Size;
		DeviationR /= (float)Size;
	}

	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, int Width, int Height, bool FirstFrame) override
	{
		const float Padding = 20.0f;
		const float HelperLineCount = 11.0f;
		const float WorkAreaHorizontal = Width - (2 * Padding);
		const float WorkAreaVertical = Height - (2 * Padding);
		const int MaxPoints = Width;
		const int Range = Height;

		Image->Clear(Color::White);

		for (int i = 0; i < HelperLineCount + 1; i++)
		{
			float VerticalY = Padding + (WorkAreaVertical / HelperLineCount) * (float)(i - 1);
			Image->DrawLine(HelperPencil2,
				Padding,
				VerticalY,
				(float)((float)Width - Padding),
				VerticalY);
		}

		float VerticalY = Padding + (WorkAreaVertical / HelperLineCount) * 10.0f;
		float VerticalYHalved = Padding + (WorkAreaVertical / HelperLineCount) * 5.0f;
		
		Image->DrawLine(HelperPencil1, Padding, Padding, Padding, VerticalY);
		Image->DrawLine(HelperPencil1, Padding, VerticalYHalved, Width - Padding, VerticalYHalved);



		float VertSeparator = (float)Width / 4.0f;
		float FirstRowHeight = VerticalY + 10.0f;
		float SecondRowHeight = FirstRowHeight + 16.0f;

		Image->DrawString(L"Signal peak"     , Text, TextColor, VertSeparator * 1, FirstRowHeight, Format);
		Image->DrawString(L"Signal average"  , Text, TextColor, VertSeparator * 2, FirstRowHeight, Format);
		Image->DrawString(L"Signal deviation", Text, TextColor, VertSeparator * 3, FirstRowHeight, Format);

		Image->DrawString(PeakL		.ToString("N3"), Text, TextColor, VertSeparator * 1 - 20, SecondRowHeight, Format);
		Image->DrawString(AvgL		.ToString("N3"), Text, TextColor, VertSeparator * 2 - 20, SecondRowHeight, Format);
		Image->DrawString(DeviationL.ToString("N3"), Text, TextColor, VertSeparator * 3 - 20, SecondRowHeight, Format);

		Image->DrawString(PeakR		.ToString("N3"), Text, TextColor, VertSeparator * 1 + 20, SecondRowHeight, Format);
		Image->DrawString(AvgR		.ToString("N3"), Text, TextColor, VertSeparator * 2 + 20, SecondRowHeight, Format);
		Image->DrawString(DeviationR.ToString("N3"), Text, TextColor, VertSeparator * 3 + 20, SecondRowHeight, Format);

		int TempH;
		TempH = PeakL * WorkAreaVertical;
		Image->FillRectangle(SignalValue, (int)VertSeparator, (int)VerticalY - TempH, 10, TempH);

	}
};
class LinearAmplifier : public DspPlugin
{
	Param UniformAmp = Param(PT_Float, L"Uniform amp", 0.0f, 2.0f, 1.0f);
	Param LeftChannelAmp =  Param(PT_Float, L"Left channel amp" , 0.0f, 2.0f, 1.0f);
	Param RightChannelAmp = Param(PT_Float, L"Right channel amp", 0.0f, 2.0f, 1.0f);

public:
	LinearAmplifier() : DspPlugin(L"Gain")
	{
		ParameterRefsForUi.push_back(&UniformAmp);
		ParameterRefsForUi.push_back(&LeftChannelAmp);
		ParameterRefsForUi.push_back(&RightChannelAmp);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; ++i)
		{
			*(BufferL++) *= LeftChannelAmp.Val  * UniformAmp.Val;
			*(BufferR++) *= RightChannelAmp.Val * UniformAmp.Val;
		}
	}
};
class Clip : public DspPlugin
{
	Param PreGain = Param(PT_Float, L"Pre Gain", 0.0f, 2.0f, 1.0f);
	Param UniformClip = Param(PT_Float, L"Uniform amp", 0.0f, 1.0f, 1.0f);
	Param LeftChannelClip = Param(PT_Float, L"Left channel amp", 0.0f, 1.0f, 1.0f);
	Param RightChannelClip = Param(PT_Float, L"Right channel amp", 0.0f, 1.0f, 1.0f);
	Param PostGain = Param(PT_Float, L"Post Gain", 0.0f, 2.0f, 1.0f);

public:
	Clip() : DspPlugin(L"Clip")
	{
		ParameterRefsForUi.push_back(&PreGain);
		ParameterRefsForUi.push_back(&UniformClip);
		ParameterRefsForUi.push_back(&LeftChannelClip);
		ParameterRefsForUi.push_back(&RightChannelClip);
		ParameterRefsForUi.push_back(&PostGain);

		UniformClip.FloatValueStep = 0.01f;
		LeftChannelClip.FloatValueStep = 0.01f;
		RightChannelClip.FloatValueStep = 0.01f;
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; ++i)
		{
			BufferL[i] *= PreGain.Val;
			BufferR[i] *= PreGain.Val;

			float LClipVal = min(UniformClip.Val, LeftChannelClip.Val);
			float RClipVal = min(UniformClip.Val, RightChannelClip.Val);

			BufferL[i] = Utilities::Clamp(BufferL[i], -LClipVal, LClipVal);
			BufferR[i] = Utilities::Clamp(BufferR[i], -RClipVal, RClipVal);
			
			BufferL[i] *= PostGain.Val;
			BufferR[i] *= PostGain.Val;
		}
	}
};
class PhaseInverter : public DspPlugin
{
	Param InvertChannel = Param(PT_Enum, L"Channels to invert", 2.0f, 4.0f, 0.0f);

public:
	PhaseInverter() : DspPlugin(L"Phase Inverter")
	{
		std::wstring* InvertChannelNames = new std::wstring[4];
		InvertChannelNames[0] = L"None";
		InvertChannelNames[1] = L"Left only";
		InvertChannelNames[2] = L"Both";
		InvertChannelNames[3] = L"Right only";
		InvertChannel.EnumNames = InvertChannelNames;

		ParameterRefsForUi.push_back(&InvertChannel);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; i++)
		{
			int EnumVal = (int)InvertChannel.Val;
			if (EnumVal == 0) continue;
			BufferL[i] = (EnumVal <= 2) ? -BufferL[i] : BufferL[i];
			BufferR[i] = (EnumVal >= 2) ? -BufferR[i] : BufferR[i];
		}
	}
};
class Bitcrusher : public DspPlugin
{
	Param Resolution = Param(PT_Float, L"New resolution", 1.0f, 16.0f, 16.0f);

#define MAX_SAMPLE_VALUE_HALVED 32768 //po³owa maksymalnej iloœci próbek w sygnale szesnastobitowym
	inline void ProcessSample(float& Sample, int Mod)
	{
		int S = (Sample + 1.0f) * (float)MAX_SAMPLE_VALUE_HALVED; 
		S += Mod / 2;
		S /= Mod;
		S *= Mod;
		Sample = ((float)S / MAX_SAMPLE_VALUE_HALVED) - 1.0f;
	}
#undef MAX_SAMPLE_VALUE_HALVED

public:
	Bitcrusher() : DspPlugin(L"Bitcrusher")
	{
		Resolution.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&Resolution);
	}

#define BIT_DEPTH 16
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int Mod = std::pow(2, BIT_DEPTH - Resolution.Val);
		for (int i = 0; i < Length; i++)
		{
			ProcessSample(BufferL[i], Mod);
			ProcessSample(BufferR[i], Mod);
		}
	}
#undef BIT_DEPTH
};
class Decimator : public DspPlugin
{
private:
	Param DecimatorPower = Param(PT_Float, L"Decimated samples", 1, 64, 1);
	float* LastPointsL;
	float* LastPointsR;
	int CurrentAllocatedPointsize = 0;
	int CurrentSample = 0;
	float PreviousSampleFinalValueL = 0.0f;
	float PreviousSampleFinalValueR = 0.0f;

	void ReallocateMemory(int PointCount)
	{
		if (CurrentAllocatedPointsize)
		{
			delete[] LastPointsL;
			delete[] LastPointsR;
		}

		CurrentAllocatedPointsize = PointCount;
		LastPointsL = new float[PointCount];
		LastPointsR = new float[PointCount];
		for (int i = 0; i < PointCount; i++)
		{
			LastPointsL[i] = 0;
			LastPointsR[i] = 0;
		}

		CurrentSample = 0;
	}

public:

	Decimator() : DspPlugin(L"Decimator")
	{
		DecimatorPower.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&DecimatorPower);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int TempPointCount = DecimatorPower.Val;
		if (CurrentAllocatedPointsize != TempPointCount) ReallocateMemory(TempPointCount);

		for (int i = 0; i < Length; i++)
		{
			if (++CurrentSample == CurrentAllocatedPointsize)
			{
				CurrentSample = 0;
				PreviousSampleFinalValueL = 0.0f;
				PreviousSampleFinalValueR = 0.0f;
				for (int j = 0; j < CurrentAllocatedPointsize; ++j) PreviousSampleFinalValueL += LastPointsL[j];
				for (int j = 0; j < CurrentAllocatedPointsize; ++j) PreviousSampleFinalValueR += LastPointsR[j];
				PreviousSampleFinalValueL /= CurrentAllocatedPointsize;
				PreviousSampleFinalValueR /= CurrentAllocatedPointsize;
			}
			
			LastPointsL[CurrentSample] = BufferL[i];
			LastPointsR[CurrentSample] = BufferR[i];
			BufferL[i] = PreviousSampleFinalValueL;
			BufferR[i] = PreviousSampleFinalValueR;
		}
	}
};
class Panner : public DspPlugin
{
	Param Balance = Param(PT_Float, L"Balance", 0.0f, 2.0f, 1.0f);

public:
	Panner() : DspPlugin(L"Panner")
	{
		Balance.FloatValueStep = 0.01f;
		ParameterRefsForUi.push_back(&Balance);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; ++i)
		{
			*(BufferL++) *= 2.0f - max(Balance.Val, 1.0f);
			*(BufferR++) *= min(Balance.Val, 1.0f);
		}
	}
};
class StereoMerger : public DspPlugin
{
	Param Type = Param(PT_Enum, L"Effect type", 0.0f, 2.0f, 0.0f);
	Param Power = Param(PT_Float, L"Power [%]", 0.0f, 1.0f, 0.0f);
	Param Clip = Param(PT_Boolean, L"Clip output", 0.0f, 1.0f, 1.0f);

public:
	StereoMerger() : DspPlugin(L"Stereo Merger")
	{
		std::wstring* TypeEnum = new std::wstring[2];
		TypeEnum[0] = L"Merge (cramp)";
		TypeEnum[1] = L"Separate (widen)";
		Type.EnumNames = TypeEnum;

		Type.FloatValueStep = 0.01f;

		ParameterRefsForUi.push_back(&Type);
		ParameterRefsForUi.push_back(&Power);
		ParameterRefsForUi.push_back(&Clip);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; i++)
		{
			float Mid = (BufferL[i] + BufferR[i]) / 2.0f;
			
			//merge
			if (Type.Val == 0.0f)
			{
				BufferL[i] = Utilities::WeightedAvg(BufferL[i], Mid, Power.Val);
				BufferR[i] = Utilities::WeightedAvg(BufferR[i], Mid, Power.Val);
			}
			//separate
			else
			{
				float Side = Mid - BufferL[i];
				BufferL[i] = BufferL[i] - (Side * Power.Val);
				BufferR[i] = BufferR[i] + (Side * Power.Val);
			}
			if (Clip.Val == 1.0f)
			{
				BufferL[i] = Utilities::Clamp(BufferL[i], -1.0f, 1.0f);
				BufferR[i] = Utilities::Clamp(BufferR[i], -1.0f, 1.0f);
			}
		}
	}
};
class StereoToMidside : public DspPlugin
{
	Param InputType = Param(PT_Enum, L"Input signal", 0.0f, 3.0f, 0.0f);
	Param RerouteLeft = Param(PT_Enum, L"Left output", 0.0f, 4.0f, 2.0f);
	Param RerouteRight = Param(PT_Enum, L"Right output", 0.0f, 4.0f, 3.0f);

public:
	StereoToMidside() : DspPlugin(L"Stereo to Mid-Side")
	{
		std::wstring* RerouteEnumL = new std::wstring[4];
		RerouteEnumL[0] = L"Left";
		RerouteEnumL[1] = L"Right";
		RerouteEnumL[2] = L"Mid";
		RerouteEnumL[3] = L"Side";
		RerouteLeft.EnumNames = RerouteEnumL;

		std::wstring* RerouteEnumR = new std::wstring[4];
		RerouteEnumR[0] = L"Left";
		RerouteEnumR[1] = L"Right";
		RerouteEnumR[2] = L"Mid";
		RerouteEnumR[3] = L"Side";
		RerouteRight.EnumNames = RerouteEnumR;

		std::wstring* RerouteEnumIn = new std::wstring[3];
		RerouteEnumIn[0] = L"Left/Right";
		RerouteEnumIn[1] = L"Mid-Side";
		RerouteEnumIn[2] = L"Side-Mid";
		InputType.EnumNames = RerouteEnumIn;

		ParameterRefsForUi.push_back(&InputType);
		ParameterRefsForUi.push_back(&RerouteLeft);
		ParameterRefsForUi.push_back(&RerouteRight);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; i++)
		{
			float L, R, Mid, Side;
			
			switch ((int)InputType.Val)
			{
			case 0: //Left/Right
				L = BufferL[i];
				R = BufferR[i];
				Mid = (L + R) / 2.0f;
				Side = Mid - L;
				break;

			case 1: //Mid-side
				Mid = BufferL[i];
				Side = BufferR[i];
				L = Mid + Side;
				R = Mid - Side;
				break;

			case 2: //Mid-side
				Mid = BufferR[i];
				Side = BufferL[i];
				L = Mid + Side;
				R = Mid - Side;
				break;
			}

			switch ((int)RerouteLeft.Val)
			{
			case 0: BufferL[i] = L; break;
			case 1: BufferL[i] = R; break;
			case 2: BufferL[i] = Mid; break;
			case 3: BufferL[i] = Side; break;
			}
			
			switch ((int)RerouteRight.Val)
			{
			case 0: BufferR[i] = L; break;
			case 1: BufferR[i] = R; break;
			case 2: BufferR[i] = Mid; break;
			case 3: BufferR[i] = Side; break;
			}

		}
	}
};
class BandpassFilterSinc : public DspPlugin
{
private:
	Param ResponseLength = Param(PT_Float, L"Impulse response length", 1, 128, 5);
	Param MuxPointCount = Param(PT_Float, L"Points to average", 0.0f, 1.0f, 1.0f);
	Param PostAmp = Param(PT_Float, L"Post amp log base", 1.0f, 10.0f, 5.0f);
	float* LastPointsL;
	float* LastPointsR;
	int CurrentAllocatedPointsize = 0;

public:

	BandpassFilterSinc() : DspPlugin(L"Band Pass Filter(sinc)")
	{
		MuxPointCount.FloatValueStep = 1.0f;
		MuxPointCount.FloatValueStep = 0.01f;
		ParameterRefsForUi.push_back(&ResponseLength);
		ParameterRefsForUi.push_back(&MuxPointCount);
		ParameterRefsForUi.push_back(&PostAmp);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		const float FrequencyCutoff = MuxPointCount.Val;
		int FilterLength = 101;
		const int FilterHalfLength = FilterLength / 2;

		float* Response = new float[FilterLength];
		float* OutL = new float[Length];
		float* OutR = new float[Length];
		for (int i = 0; i < Length; i++)
		{
			OutL[i] = 0.0f;
			OutR[i] = 0.0f;
		}
		
		float ResponseSum = 0.0f;

		for (int i = 0; i < FilterLength; ++i)
		{
			int Condition = i - FilterHalfLength;

			if (Condition == 0) Response[i] = 2.0f * M_PI * FrequencyCutoff;
			else Response[i] = sin(2.0f * M_PI * FrequencyCutoff * (float)Condition) / (float)Condition;
			Response[i] *= 0.54f - (0.46f * cos(2.0f * M_PI * (float)i / (float)FilterLength));
			ResponseSum += Response[i];
		}
		for (int i = 0; i < FilterLength; ++i) Response[i] /= ResponseSum;
		
		for (int i = FilterLength - 1; i < Length; ++i)
		{
			for (int j = 0; j < FilterLength; ++j)
			{
				OutL[i] += BufferL[i - j] * Response[j];
				OutR[i] += BufferR[i - j] * Response[j];
			}
		}

		float PostAmpValue = pow(2, (int)PostAmp.Val - 4);

		for (int i = 0; i < Length; ++i)
		{
			BufferL[i] = (i >= FilterLength) ? Utilities::Clamp(OutL[i] * PostAmpValue, -1.0f, 1.0f) : 0.0f;
			BufferR[i] = (i >= FilterLength) ? Utilities::Clamp(OutR[i] * PostAmpValue, -1.0f, 1.0f) : 0.0f;
		}

		delete[] OutL;
		delete[] OutR;
		delete[] Response;
	}
};
class LowpassFilterAvg : public DspPlugin
{
private:
	Param MuxPointCount = Param(PT_Float, L"Points to average", 1, 128, 5);
	float* LastPointsL;
	float* LastPointsR;
	int CurrentAllocatedPointsize = 0;

	void ReallocateMemory(int MuxPointCount)
	{
		if (CurrentAllocatedPointsize)
		{
			delete[] LastPointsL;
			delete[] LastPointsR;
		}

		CurrentAllocatedPointsize = MuxPointCount;
		LastPointsL = new float[MuxPointCount];
		LastPointsR = new float[MuxPointCount];
		for (int i = 0; i < MuxPointCount; i++)
		{
			LastPointsL[i] = 0;
			LastPointsR[i] = 0;
		}
	}

public:

	LowpassFilterAvg() : DspPlugin(L"Low Pass Filter (avg)")
	{
		MuxPointCount.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&MuxPointCount);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int TempMuxPointCount = MuxPointCount.Val;

		if (CurrentAllocatedPointsize != TempMuxPointCount) ReallocateMemory(TempMuxPointCount);

		float* LCopy = new float[Length + TempMuxPointCount];
		float* RCopy = new float[Length + TempMuxPointCount];

		for (int i = 0; i < TempMuxPointCount; i++)
		{
			LCopy[i] = LastPointsL[i];
			RCopy[i] = LastPointsR[i];
		}

		for (int i = 0; i < Length; i++)
		{
			LCopy[i + TempMuxPointCount] = BufferL[i];
			RCopy[i + TempMuxPointCount] = BufferR[i];
		}

		for (int i = 0; i < Length; i++)
		{
			BufferL[i] = 0;
			BufferR[i] = 0;

			for (int j = i; j < i + TempMuxPointCount; j++)
			{
				BufferL[i] += LCopy[j];
				BufferR[i] += RCopy[j];
			}

			BufferL[i] /= (float)TempMuxPointCount;
			BufferR[i] /= (float)TempMuxPointCount;
		}

		for (int i = 0; i < TempMuxPointCount; i++)
		{
			LastPointsL[i] = LCopy[Length + i];
			LastPointsR[i] = RCopy[Length + i];
		}

		delete[] LCopy;
		delete[] RCopy;
	}
};
class RetriggerSimple : public DspPlugin
{
private:
	Param Modulo = Param(PT_Float, L"Retrigger modulo", 0, 6, 1);

public:
	RetriggerSimple() : DspPlugin(L"Retrigger (Simple)")
	{
		Modulo.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&Modulo);
	}
	
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int ModuloVal = Length / std::pow(2, Modulo.Val);

		for (int i = 0; i < Length; i++)
		{
			BufferL[i] = BufferL[i % ModuloVal];
			BufferR[i] = BufferR[i % ModuloVal];
		}
	}
};
class Retrigger : public DspPlugin
{
private:
	Param SampleLength = Param(PT_Float, L"Sample length [ms]", 0.1f, 500.0f, 100.0f);
	Param Modulo = Param(PT_Float, L"Repeat count", 1.0f, 20.0f, 1.0f);
	
	gcroot<MonitoredArray<float>^> DataL;
	gcroot<MonitoredArray<float>^> DataR;
	int RepeatState = 1;
	int RepeatSample = 0;

public:
	Retrigger() : DspPlugin(L"Retrigger")
	{
		Modulo.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&SampleLength);
		ParameterRefsForUi.push_back(&Modulo);

		DataL = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataR = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int PointsSize = (float)AUDIO_SAMPLERATE * (float)SampleLength.Val / 1000.0f;
		int ArrSize = DataL->Size();
		for (int i = 0; i < Length; ++i)
		{
			if (Modulo.Val == 1.0f)
			{
				DataL->Empty();
				DataR->Empty();
				break;
			}

			if (ArrSize < PointsSize)
			{
				DataL->PushLast(BufferL[i]);
				DataR->PushLast(BufferR[i]);
				++ArrSize;
				continue;
			}

			BufferL[i] = DataL->Get(RepeatSample);
			BufferR[i] = DataR->Get(RepeatSample);
			++RepeatSample;
			if (RepeatSample < PointsSize) continue;

			RepeatSample = 0;
			++RepeatState;
			if (RepeatState < Modulo.Val) continue;

			RepeatState = 1;
			DataL->Empty();
			DataR->Empty();
			ArrSize = 0;
		}
	}
};
class ReverserSimple : public DspPlugin
{
public:
	ReverserSimple() : DspPlugin(L"Reverser (Simple)") { }

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int HalfLength = Length / 2;
		for (int i = 0; i < HalfLength; i++)
		{
			Utilities::Swap(BufferL[i], BufferL[Length - i - 1]);
			Utilities::Swap(BufferR[i], BufferR[Length - i - 1]);
		}
	}
};
class Reverser : public DspPlugin
{
private:
	Param SampleLength = Param(PT_Float, L"Sample length [ms]", 0.1f, 500.0f, 100.0f);

	gcroot<MonitoredArray<float>^> DataL1;
	gcroot<MonitoredArray<float>^> DataR1;
	gcroot<MonitoredArray<float>^> DataL2;
	gcroot<MonitoredArray<float>^> DataR2;
	int State = 0; //0 - nagrywanie wstêpne do pierwszego bufora
	               //1 - nagrywa drugi, odtwarza pierwszy
	               //2 - nagrywa pierwszy, odtwarza drugi

	int OldPointsize = 0;

	inline void NextState()
	{
		switch (State)
		{
		case 1:
			State = 2;
			DataL1->Empty();
			DataR1->Empty();
			break;
		
		case 0:
		case 2:
			State = 1;
			DataL2->Empty();
			DataR2->Empty();
			break;
		}
	}

public:
	Reverser() : DspPlugin(L"Reverser")
	{
		ParameterRefsForUi.push_back(&SampleLength);

		DataL1 = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataR1 = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataL2 = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataR2 = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int PointsSize = (float)AUDIO_SAMPLERATE * (float)SampleLength.Val / 1000.0f;
		if (OldPointsize != PointsSize)
		{
			DataL1->Empty();
			DataR1->Empty();
			DataL2->Empty();
			DataR2->Empty();
			State = 0;
		}
		OldPointsize = PointsSize;

		for (int i = 0; i < Length; ++i)
		{
			int ArrSize = (State != 1) ? DataL1->Size() : DataL2->Size();
			switch (State)
			{
			case 0:
				DataL1->PushLast(BufferL[i]);
				DataR1->PushLast(BufferR[i]);
				BufferL[i] = 0.0f;
				BufferR[i] = 0.0f;
				break;

			case 1:
				DataL2->PushLast(BufferL[i]);
				DataR2->PushLast(BufferR[i]);
				BufferL[i] = DataL1->Get(PointsSize - ArrSize);
				BufferR[i] = DataR1->Get(PointsSize - ArrSize);
				break;
				
			case 2:
				DataL1->PushLast(BufferL[i]);
				DataR1->PushLast(BufferR[i]);
				BufferL[i] = DataL2->Get(PointsSize - ArrSize);
				BufferR[i] = DataR2->Get(PointsSize - ArrSize);
				break;
			}
			
			if (ArrSize < PointsSize) continue;
			NextState();
		}
	}
};
#endif
#undef Val
