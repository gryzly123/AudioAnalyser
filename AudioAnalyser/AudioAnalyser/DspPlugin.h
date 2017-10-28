#pragma once
#include <string>
#include <vector>
#include "Utilities.h"

enum DspPluginParameterType
{
	PT_Boolean,
	PT_Float,
	PT_Enum
};

public struct DspPluginParameter
{
	const DspPluginParameterType Type;
	const std::wstring Name;
	const std::wstring* EnumNames;
	const float MinimumValue = 0.0f;
	const float MaximumValue = 1.0f;
	float CurrentValue = 0.0f;


	DspPluginParameter(DspPluginParameterType Type, std::wstring Name, float MinimumValue = 0.0f, float MaximumValue = 1.0f, float CurrentValue = 0.0f, std::wstring* EnumNames = nullptr)
		: Type(Type), Name(Name), MinimumValue(MinimumValue), MaximumValue(MaximumValue), CurrentValue(CurrentValue), EnumNames(EnumNames) { }

	~DspPluginParameter()
	{
		if (EnumNames) delete[] EnumNames;
	}

private:
	DspPluginParameter() : Type(PT_Float), Name(L"null"), MinimumValue(0), MaximumValue(0), CurrentValue(0), EnumNames(nullptr) { }
};

typedef DspPluginParameter Param;
#define Val CurrentValue

class DspPlugin
{
protected:
	std::vector<DspPluginParameter*> ParameterRefsForUi;
	DspPlugin(const std::wstring PluginName) : PluginName(PluginName) { }

public:
	const std::wstring PluginName;
	bool Bypass = false;
	bool Solo = false;
	float DryWetMix = 1.0f;
	bool HasVisualization = false;

	std::vector<DspPluginParameter*> GetParameters() { return ParameterRefsForUi; }
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) = 0;
};

class NullPlugin : public DspPlugin
{
public:
	NullPlugin() : DspPlugin(L"(none)") { }
	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override { }
};

class LinearAmplifier : public DspPlugin
{
	Param LeftChannelAmp =  Param(PT_Float, L"Left channel amp" , 0.0f, 8.0f, 1.0f);
	Param RightChannelAmp = Param(PT_Float, L"Right channel amp", 0.0f, 8.0f, 1.0f);

public:
	LinearAmplifier() : DspPlugin(L"Linear Amplifier")
	{
		ParameterRefsForUi.push_back(&LeftChannelAmp);
		ParameterRefsForUi.push_back(&RightChannelAmp);
	}

	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		for (int i = 0; i < Length; ++i)
		{
			*(BufferL++) *= LeftChannelAmp.Val;
			*(BufferR++) *= RightChannelAmp.Val;
		}
	}
};

class SineWaveGenerator : public DspPlugin
{
private:
	float SineStatus = 0;
	float SineInc = 0;

	Param SineAmp = Param(PT_Float, L"Sine volume", 0.0f, 1.0f, 0.6f);
	Param SineFrequency = Param(PT_Float, L"Sine frequency", 20.0f, 22500.0f, 100.0f);
	Param InvertPhase = Param(PT_Boolean, L"Invert phase", 0.0f, 1.0f, 1.0f);

public:
	SineWaveGenerator() : DspPlugin(L"Sine wave")
	{
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

class RetriggerSimple : public DspPlugin
{
private:
	Param Modulo = Param(PT_Enum, L"Retrigger modulo", 0, 6, 3);

public:
	RetriggerSimple() : DspPlugin(L"Retrigger (simple)")
	{
		std::wstring* ModuloEnum = new std::wstring[6];
		ModuloEnum[0] = L"256";
		ModuloEnum[1] = L"512";
		ModuloEnum[2] = L"1024";
		ModuloEnum[3] = L"2048";
		ModuloEnum[4] = L"4096";
		ModuloEnum[5] = L"8196";
		Modulo.EnumNames = ModuloEnum;

		ParameterRefsForUi.push_back(&Modulo);
	}


	virtual void ProcessData(float* BufferL, float* BufferR, int Length) override
	{
		int ModuloVal = std::pow(2, (Modulo.Val + 9));

		for (int i = 0; i < Length; i++)
		{
			BufferL[i] = BufferL[i % ModuloVal];
			BufferR[i] = BufferR[i % ModuloVal];
		}
	}
};

#undef Val
