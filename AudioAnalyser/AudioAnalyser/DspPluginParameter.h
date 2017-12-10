#pragma once
#include "PCH.h"

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
	std::wstring* EnumNames;
	const float MinimumValue = 0.0f;
	const float MaximumValue = 1.0f;
	float CurrentValue = 0.0f;
	float FloatValueStep = 0.1f;

	DspPluginParameter(DspPluginParameterType Type, std::wstring Name, float MinimumValue = 0.0f, float MaximumValue = 1.0f, float CurrentValue = 0.0f)
		: Type(Type), Name(Name), MinimumValue(MinimumValue), MaximumValue(MaximumValue), CurrentValue(CurrentValue), EnumNames(nullptr) { }

	~DspPluginParameter()
	{
		if (EnumNames) delete[] EnumNames;
	}

	void UpdateParameterUnsafe(float NewValue)
	{
		if (NewValue < MinimumValue) NewValue = MinimumValue;
		if (NewValue > MaximumValue) NewValue = MaximumValue;
		switch (Type)
		{
			//Upewniamy siê, ¿e nowa wartoœæ parameteru znajduje siê na wartoœciach krokowych FloatValueStep
		case PT_Float:
		{
			float TempVal = (NewValue - MinimumValue) / FloatValueStep;
			int TempStep = (int)TempVal;
			NewValue = (float)TempStep * FloatValueStep;
			NewValue += MinimumValue;
			CurrentValue = NewValue;
		}
		break;

		//Upewniamy siê, ¿e nowa wartoœæ parameteru ma zerow¹ czêœæ przecinkow¹
		case PT_Boolean:
		case PT_Enum:
			CurrentValue = floorf(NewValue);
			break;
		}
	}

private:
	DspPluginParameter() : Type(PT_Float), Name(L"null"), MinimumValue(0), MaximumValue(0), CurrentValue(0), EnumNames(nullptr) { }
};
