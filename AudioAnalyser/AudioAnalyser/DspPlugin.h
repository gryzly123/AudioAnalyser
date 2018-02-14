#pragma once
#include "PCH.h"
#include "DspPluginParameter.h"
#include "DynamicPluginVizWindow.h"

using namespace AudioAnalyser;
using namespace System;

typedef DspPluginParameter Param;

class DspPlugin
{
protected:
	std::vector<DspPluginParameter*> ParameterRefsForUi;
	DspPlugin(const std::wstring PluginName, const bool HasVisualization = false)
		: PluginName(PluginName),
		HasVisualization(HasVisualization) { }

	static PrecomputedSin* PcSin;

public:
	const std::wstring PluginName;
	bool Bypass = false;
	float DryWetMix = 1.0f;
	const bool HasVisualization = false;

	std::vector<DspPluginParameter*> GetParameters() { return ParameterRefsForUi; }
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) = 0;
	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame) { }
};

class NullPlugin : public DspPlugin
{
public:
	NullPlugin();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length);
};

class SineWaveGenerator : public DspPlugin
{
private:
	float SineStatus = 0;
	float LastFreq = 0;

	Param SineAmp = Param(PT_Float, L"Sine volume", 0.0f, 1.0f, 0.6f);
	Param SineFrequency = Param(PT_Float, L"Sine frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 0.0f);
	Param Retrigger = Param(PT_Boolean, L"Reset on freq. change", 0.0f, 1.0f, 0.0f);

public:
	SineWaveGenerator();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class SawWaveGenerator : public DspPlugin
{
private:
	float TimeStatus = 0.0f;
	float TimeIncrementation = 0.0f;
	float TempValue = 0.0f;

	Param Amp = Param(PT_Float, L"Saw volume", 0.0f, 1.0f, 0.6f);
	Param Frequency = Param(PT_Float, L"Saw frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 0.0f);
	Param Retrigger = Param(PT_Boolean, L"Reset on freq. change", 0.0f, 1.0f, 0.0f);
	Param UseEquation = Param(PT_Boolean, L"Use additive synthesis", 0.0f, 1.0f, 0.0f);
	Param EquationN = Param(PT_Float, L"Additive sine count", 1.0f, 100.0f, 30.0f);
public:
	SawWaveGenerator();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class SquareWaveGenerator : public DspPlugin
{
private:
	float TimeStatus = 0.0f;
	float TimeIncrementation = 0.0f;
	float TempValue = 0.0f;

	Param Amp = Param(PT_Float, L"Saw volume", 0.0f, 1.0f, 0.6f);
	Param Frequency = Param(PT_Float, L"Saw frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 0.0f);
	Param Retrigger = Param(PT_Boolean, L"Reset on freq. change", 0.0f, 1.0f, 0.0f);
	Param UseEquation = Param(PT_Boolean, L"Use additive synthesis", 0.0f, 1.0f, 0.0f);
	Param EquationN = Param(PT_Float, L"Additive sine count", 1.0f, 100.0f, 30.0f);

public:
	SquareWaveGenerator();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class WhiteNoiseGenerator : public DspPlugin
{
private:
	Param Amp = Param(PT_Float, L"Noise volume", 0.0f, 1.0f, 0.2f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 0.0f);
	Param EquationN = Param(PT_Float, L"Random() count", 1.0f, 12.0f, 4.0f);
	gcroot<Random^> RNG;
	float TempValue = 0.0f;

public:
	WhiteNoiseGenerator();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Oscilloscope : public DspPlugin
{
	Param CurveDuration = Param(PT_Float, L"Curve duration [ms]", 1.0f, 200.0f, 20.0f);
	Param Channels = Param(PT_Enum, L"Channels", 2.0f, 3.0f, 1.0f);

	gcroot<MonitoredArray<float>^> Data;
	gcroot<MonitoredArray<float>^> Interp;
	gcroot<Pen^>                   DataPencil;
	gcroot<SolidBrush^>            DataBrush;
	gcroot<Pen^>                   HelperPencil1;
	gcroot<Pen^>                   HelperPencil2;
	gcroot<Font^>                  TextL;
	gcroot<Font^>                  TextS;
	gcroot<StringFormat^>          FormatC;
	gcroot<StringFormat^>          FormatR;
	gcroot<Brush^>                 TextColor;

public:
	Oscilloscope();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame) override;
};

class Spectrum : public DspPlugin
{
	Param CurveDuration = Param(PT_Enum, L"Samples", 0.0f, 6.0f, 1.0f);
	Param Channels = Param(PT_Enum, L"Channel", 2.0f, 3.0f, 1.0f);
	Param ZoomL = Param(PT_Float, L"Cut below", 0.0f, (float)(AUDIO_SAMPLERATE / 2), 0.0f);
	Param ZoomR = Param(PT_Float, L"Cut above", 0.0f, (float)(AUDIO_SAMPLERATE / 2), (float)(AUDIO_SAMPLERATE / 2));
	Param ZoomV = Param(PT_Float, L"Vertical range", 0.1f, 1.0f, 1.0f);

	gcroot<MonitoredArray<float>^> Data;
	gcroot<Pen^>                   DataPencil;
	gcroot<SolidBrush^>            DataBrush;
	gcroot<Pen^>                   HelperPencil1;
	gcroot<Pen^>                   HelperPencil2;
	gcroot<Font^>                  TextL;
	gcroot<Font^>                  TextS;
	gcroot<StringFormat^>          FormatC;
	gcroot<StringFormat^>          FormatR;
	gcroot<Brush^>                 TextColor;

public:
	Spectrum();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame) override;
};

class Spectrogram : public DspPlugin
{
	Param CurveDuration = Param(PT_Enum, L"Samples", 0.0f, 6.0f, 1.0f);
	Param Channels = Param(PT_Enum, L"Channel", 2.0f, 3.0f, 1.0f);
	Param ContrastBump = Param(PT_Float, L"Contrast Amp", 0.0f, 10.0f, 0.0f);

	gcroot<MonitoredArray<float>^> Data;

public:
	Spectrogram();

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
	virtual void UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame) override;
};

class LinearAmplifier : public DspPlugin
{
	Param UniformAmp = Param(PT_Float, L"Uniform amp", 0.0f, 2.0f, 1.0f);
	Param LeftChannelAmp =  Param(PT_Float, L"Left channel amp" , 0.0f, 2.0f, 1.0f);
	Param RightChannelAmp = Param(PT_Float, L"Right channel amp", 0.0f, 2.0f, 1.0f);

public:
	LinearAmplifier();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Clip : public DspPlugin
{
	Param PreGain = Param(PT_Float, L"Pre Gain", 0.0f, 2.0f, 1.0f);
	Param UniformClip = Param(PT_Float, L"Uniform amp", 0.0f, 1.0f, 1.0f);
	Param LeftChannelClip = Param(PT_Float, L"Left channel amp", 0.0f, 1.0f, 1.0f);
	Param RightChannelClip = Param(PT_Float, L"Right channel amp", 0.0f, 1.0f, 1.0f);
	Param PostGain = Param(PT_Float, L"Post Gain", 0.0f, 2.0f, 1.0f);

public:
	Clip();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class PhaseInverter : public DspPlugin
{
	Param InvertChannel = Param(PT_Enum, L"Channels to invert", 2.0f, 4.0f, 0.0f);

public:
	PhaseInverter();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Bitcrusher : public DspPlugin
{
	Param Resolution = Param(PT_Float, L"New resolution", 1.0f, 16.0f, 16.0f);

	inline void ProcessSample(float& Sample, int Mod);

public:
	Bitcrusher();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
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

	void ReallocateMemory(int PointCount);

public:
	Decimator();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Panner : public DspPlugin
{
	Param Balance = Param(PT_Float, L"Balance", 0.0f, 2.0f, 1.0f);

public:
	Panner();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class StereoMerger : public DspPlugin
{
	Param Type = Param(PT_Enum, L"Effect type", 0.0f, 2.0f, 0.0f);
	Param Power = Param(PT_Float, L"Power [%]", 0.0f, 1.0f, 0.0f);
	Param Clip = Param(PT_Boolean, L"Clip output", 0.0f, 1.0f, 1.0f);

public:
	StereoMerger();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class StereoToMidside : public DspPlugin
{
	Param InputType = Param(PT_Enum, L"Input signal", 0.0f, 3.0f, 0.0f);
	Param RerouteLeft = Param(PT_Enum, L"Left output", 0.0f, 4.0f, 2.0f);
	Param RerouteRight = Param(PT_Enum, L"Right output", 0.0f, 4.0f, 3.0f);

public:
	StereoToMidside();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class SincFilter : public DspPlugin
{
protected:
	float* LastPointsL;
	float* LastPointsR;
	float* Response;
	int CurrentAllocatedPointsize = 0;
	float LastKnownCutoffFrequency = -1.0f;

	Param CutoffFrequency = Param(PT_Float, L"Cutoff frequency", 1.0f, AUDIO_SAMPLERATE / 2.0f, 200.0f);

	virtual void GenerateSincFunction() = 0;

public:
	SincFilter(std::wstring ChildFilterName);
	void SaveLastPoints(float* BufferL, float* BufferR, int Length);
	inline float GetPoint(int Index, float* SubzeroBufferPtr, float* BufferPtr);
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class LowPassFilterSinc : public SincFilter
{
public:
	LowPassFilterSinc();

private:
	virtual void GenerateSincFunction() override;
};

class LowpassFilterAvg : public DspPlugin
{
private:
	float* LastPointsL;
	float* LastPointsR;
	int CurrentAllocatedPointsize = 0;

	Param CutoffFrequency = Param(PT_Float, L"Points to average", 1, 128, 5);

	void ReallocateMemory(int CutoffFrequency);

public:
	LowpassFilterAvg();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class RetriggerSimple : public DspPlugin
{
private:
	Param Modulo = Param(PT_Float, L"Retrigger modulo", 0, 6, 1);

public:
	RetriggerSimple();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Retrigger : public DspPlugin
{
private:
	Param SampleLength = Param(PT_Float, L"Sample length [ms]", 0.1f, 500.0f, 100.0f);
	Param Modulo = Param(PT_Float, L"Repeat count", 1.0f, 20.0f, 1.0f);
	
	std::deque<float> DataL;
	std::deque<float> DataR;
	int RepeatState = 1;
	int RepeatSample = 0;

public:
	Retrigger();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class ReverserSimple : public DspPlugin
{
public:
	ReverserSimple();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};

class Reverser : public DspPlugin
{
private:
	Param SampleLength = Param(PT_Float, L"Sample length [ms]", 0.1f, 500.0f, 100.0f);

	std::deque<float> DataL1;
	std::deque<float> DataR1;
	std::deque<float> DataL2;
	std::deque<float> DataR2;

	int State = 0; //0 - nagrywanie wstêpne do pierwszego bufora
	               //1 - nagrywa drugi, odtwarza pierwszy
	               //2 - nagrywa pierwszy, odtwarza drugi

	int OldPointsize = 0;

	inline void NextState();

public:
	Reverser();
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override;
};
