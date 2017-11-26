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
			float Value = SineAmp.Val * sin(SineStatus * 2 * 3.141591);
			BufferL[i] = Value;
			BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * Value : Value;
		}
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

class Oscilloscope : public DspPlugin
{
	Param CurveDuration = Param(PT_Float, L"Curve duration [ms]", 1.0f, 200.0f, 20.0f);
	Param Channels = Param(PT_Enum, L"Channels", 2.0f, 4.0f, 1.0f);
	Param ImgPadding = Param(PT_Float, L"Margin [px]", 1.0f, 20.0f, 10.0f);

	gcroot<MonitoredArray<float>^> DataL, DataR;

public:
	Oscilloscope() : DspPlugin(L"Oscilloscope", HAS_VIZ)
	{
		std::wstring* ChannelNames = new std::wstring[4];
		ChannelNames[0] = L"Left";
		ChannelNames[1] = L"Right";
		ChannelNames[2] = L"Mixdown";
		ChannelNames[3] = L"Both";
		Channels.EnumNames = ChannelNames;

		ImgPadding.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&Channels);
		ParameterRefsForUi.push_back(&CurveDuration);
		ParameterRefsForUi.push_back(&ImgPadding);

		DataL = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
		DataR = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int CurvePointsSize = (float)AUDIO_SAMPLERATE * (float)CurveDuration.Val / 1000.0f;

		DataL->Lock();
		for (int i = 0; i < Length; ++i) DataL->PushLast(BufferL[i]);
		int ExcessData = DataL->Size() - CurvePointsSize;
		while (--ExcessData > 0) DataL->PopFirst();
		DataL->Unlock();

		DataR->Lock();
		for (int i = 0; i < Length; ++i) DataR->PushLast(BufferL[i]);
		ExcessData = DataR->Size() - CurvePointsSize;
		while (--ExcessData > 0) DataR->PopFirst();
		DataR->Unlock();
	}

	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, int Width, int Height, bool FirstFrame) override
	{
		const int Padding = ImgPadding.Val;
		const int HelperLineCount = 10;
		int MaxPoints = Width;
		int Range = Height;
		
		Image->Clear(Color::White);
		Pen^ DataPencil = gcnew Pen(Color::Black, 2);
		Pen^ HelperPencil1 = gcnew Pen(Color::Gray, 1);
		Pen^ HelperPencil2 = gcnew Pen(Color::Gray, 1);
		HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;

		Image->DrawLine(HelperPencil1, Padding, Padding, Padding, Height - Padding);
		Image->DrawLine(HelperPencil1, Padding, Height - Padding, Width - Padding, Height - Padding);

		int WorkAreaHorizontal = Width - (2 * Padding);
		int WorkAreaVertical = Height - (2 * Padding);

		for (int i = 1; i < HelperLineCount + 1; i++)
		{
			Image->DrawLine(HelperPencil2, Padding + (WorkAreaHorizontal / HelperLineCount) * i, Padding, Padding + (WorkAreaHorizontal / HelperLineCount) * i, Height - Padding);
		}

		MonitoredArray<float>^ InterpolatedData = gcnew MonitoredArray<float>();
		DataL->Lock();
		Utilities::LinearInterpolateArrays((MonitoredArray<float>^)DataL, InterpolatedData, WorkAreaHorizontal);
		DataL->Unlock();


		for (int i = 1; i < WorkAreaHorizontal; ++i)
		{
			int HorizontalVal = i + Padding;
			int y1 = (int)(Range / 2 + ((Single)WorkAreaVertical / 2 * (Single)InterpolatedData->operator[](i - 1)));
			int y2 = (int)(Range / 2 + ((Single)WorkAreaVertical / 2 * (Single)InterpolatedData->operator[](i)));
			if (y1 == y2) y2++;
			Image->DrawLine(DataPencil, HorizontalVal, y1, HorizontalVal, y2);
		}

		Image->DrawLine(gcnew Pen(Color::Green), 1, 1, DataL->Size() + 2, 1);

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

#define MAX_SAMPLE_VALUE_HALVED 32768 //po�owa maksymalnej ilo�ci pr�bek w sygnale szesnastobitowym
#define BIT_DEPTH 16

	inline void ProcessSample(float& Sample)
	{
		int S = Sample * (float)MAX_SAMPLE_VALUE_HALVED; 
		int Mod = std::pow(2, BIT_DEPTH + 1 - Resolution.Val);
		
		S += MAX_SAMPLE_VALUE_HALVED;
		S /= Mod;
		S *= Mod;
		S -= MAX_SAMPLE_VALUE_HALVED;

		Sample = (float)S / MAX_SAMPLE_VALUE_HALVED;
	}

#undef MAX_SAMPLE_VALUE_HALVED
#undef BIT_DEPTH

public:
	Bitcrusher() : DspPlugin(L"Bitcrusher")
	{
		Resolution.FloatValueStep = 1.0f;

		ParameterRefsForUi.push_back(&Resolution);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; i++)
		{
			ProcessSample(BufferL[i]);
			ProcessSample(BufferR[i]);
		}
	}
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

		delete LCopy;
		delete RCopy;
	}
};
class RetriggerSimple : public DspPlugin
{
private:
	Param Modulo = Param(PT_Float, L"Retrigger modulo", 0, 6, 1);

public:
	RetriggerSimple() : DspPlugin(L"Retrigger (Simple)")
	{
		//std::wstring* ModuloEnum = new std::wstring[6];
		//ModuloEnum[0] = L"256";
		//ModuloEnum[1] = L"512";
		//ModuloEnum[2] = L"1024";
		//ModuloEnum[3] = L"2048";
		//ModuloEnum[4] = L"4096";
		//ModuloEnum[5] = L"8192";
		//Modulo.EnumNames = ModuloEnum;

		Modulo.FloatValueStep = 1.0f;
		ParameterRefsForUi.push_back(&Modulo);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		//int ModuloVal = std::pow(2, (Modulo.Val + 8));
		int ModuloVal = Length / std::pow(2, Modulo.Val);

		for (int i = 0; i < Length; i++)
		{
			BufferL[i] = BufferL[i % ModuloVal];
			BufferR[i] = BufferR[i % ModuloVal];
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
#endif
#undef Val
