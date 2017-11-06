#include "PCH.h"
#include "AudioProcessor.h"

AudioProcessor* AudioProcessor::Instance = nullptr;

AudioProcessor::AudioProcessor()
{
	for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i) Plugins.push_back(new NullPlugin());
}

AudioProcessor::~AudioProcessor()
{
	for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i) delete Plugins[i];
}

DspPlugin* AudioProcessor::PluginFactory(std::wstring NewPluginName)
{
	if (NewPluginName == (L"None")) return new NullPlugin();
	if (NewPluginName == (L"(none)")) return new NullPlugin();

	if (NewPluginName == (L"Sine Wave")) return new SineWaveGenerator();
	//if (NewPluginName == (L"Saw Wave")) return new ();
	//if (NewPluginName == (L"Square Wave")) return new ();
	//if (NewPluginName == (L"White noise")) return new ();

	//if (NewPluginName == (L"Oscilloscope")) return new ();
	//if (NewPluginName == (L"Spectrum")) return new ();
	//if (NewPluginName == (L"Spectrogram")) return new ();
	//if (NewPluginName == (L"Signal Parameters")) return new ();
	
	if (NewPluginName == (L"Gain")) return new LinearAmplifier();
	if (NewPluginName == (L"Clip")) return new Clip();
	if (NewPluginName == (L"Phase Inverter")) return new PhaseInverter();
	
	if (NewPluginName == (L"Bitcrusher")) return new Bitcrusher();
	if (NewPluginName == (L"Decimator")) return new Decimator();

	if (NewPluginName == (L"Panner")) return new Panner();
	//if (NewPluginName == (L"Stereo Separator")) return new ();
	if (NewPluginName == (L"Stereo to Mid-Side")) return new StereoToMidside();
	if (NewPluginName == (L"Low Pass Filter (avg)")) return new LowpassFilterAvg();
	//if (NewPluginName == (L"Low Pass Filter (sinc)")) return new ();
	//if (NewPluginName == (L"High Pass Filter (sinc)")) return new ();
	//if (NewPluginName == (L"Band Pass Filter (sinc)")) return new ();

	//if (NewPluginName == (L"Delay")) return new ();
	if (NewPluginName == (L"Retrigger (Simple)")) return new RetriggerSimple();
	//if (NewPluginName == (L"Retrigger")) return new ();
	if (NewPluginName == (L"Reverser (Simple)")) return new ReverserSimple();
	//if (NewPluginName == (L"Reverser")) return new ();

	Utilities::ShowMessageboxDebugonly(L"No plugins found. Using null");
	return new NullPlugin();
}

AudioProcessor* AudioProcessor::GetInstance()
{
	if (!Instance) Instance = new AudioProcessor();
	return Instance;
}

void AudioProcessor::ChangePlugin(int AtIndex, const std::wstring NewPluginName)
{
	DspPlugin* Temp = Plugins[AtIndex];
	float DryWetMix = Temp->DryWetMix;
	
	Plugins[AtIndex] = new NullPlugin();
	Plugins[AtIndex] = PluginFactory(NewPluginName);
	Plugins[AtIndex]->DryWetMix = DryWetMix;
	
	delete Temp;
}

void AudioProcessor::SwapPlugins(int AtIndex, PluginSwapDirection Direction)
{
	int Id1 = AtIndex;
	int Id2 = Direction ? AtIndex + 1 : AtIndex - 1;

	DspPlugin* SwapHelper = Plugins[Id1];
	float DryWetMixHelper = Plugins[Id1]->DryWetMix;

	Plugins[Id1]->DryWetMix = Plugins[Id2]->DryWetMix;
	Plugins[Id2]->DryWetMix = DryWetMixHelper;

	Plugins[Id1] = Plugins[Id2];
	Plugins[Id2] = SwapHelper;
}

void AudioProcessor::SetPluginVolumeMix(int AtIndex, float Value)
{
	Plugins[AtIndex]->DryWetMix = Value;
}

float AudioProcessor::GetPluginVolumeMix(int AtIndex)
{
	return Plugins[AtIndex]->DryWetMix;
}

std::vector<DspPluginParameter*> AudioProcessor::GetPluginParameters(int AtIndex)
{
	return Plugins[AtIndex]->GetParameters();
}

void AudioProcessor::UpdatePluginParameterByIndex(int PluginIndex, int AtIndex, float NewValue)
{
	DspPluginParameter* Param = Plugins[PluginIndex]->GetParameters()[AtIndex];
	Param->CurrentValue = NewValue;
}

void AudioProcessor::UpdatePluginParameterByName(int PluginIndex, std::wstring AtName, float NewValue)
{
	System::String^ Str = PluginIndex.ToString() + " PARAM " + ToCli(AtName) + " " + NewValue.ToString();
	System::Windows::Forms::Break(Str);

	for (DspPluginParameter* Param : Plugins[PluginIndex]->GetParameters())
	{
		if (Param->Name == AtName)
		{
			Param->UpdateParameterUnsafe(NewValue);
			break;
		}
	}
}


std::wstring AudioProcessor::GetPluginName(int AtIndex)
{
	return Plugins[AtIndex]->PluginName;
}

bool AudioProcessor::IsPluginBypassed(int AtIndex)
{
	return Plugins[AtIndex]->Bypass;
}

void AudioProcessor::SetPluginBypassed(int AtIndex)
{
	Plugins[AtIndex]->Bypass = !Plugins[AtIndex]->Bypass;
}

void AudioProcessor::SetPluginBypassed(int AtIndex, bool NewBypassed)
{
	Plugins[AtIndex]->Bypass = NewBypassed;
}

void AudioProcessor::SetPluginSolo(int AtIndex)
{
	bool IsAlreadySolo = true;
	for (int i = 0; i < GUI_RACKITEMS_COUNT; i++)
		if (i != AtIndex && !Plugins[i]->Bypass) IsAlreadySolo = false;

	if (IsAlreadySolo)
	{
		for (int i = 0; i < GUI_RACKITEMS_COUNT; i++) Plugins[i]->Bypass = false;
	}
	else
	{
		for (int i = 0; i < GUI_RACKITEMS_COUNT; i++) Plugins[i]->Bypass = true;
		Plugins[AtIndex]->Bypass = false;
	}
}

void AudioProcessor::GetPluginWindowCapabilities(int AtIndex, bool& HasConfig, bool& HasVis)
{
	HasConfig = Plugins[AtIndex]->GetParameters().size();
	HasVis = Plugins[AtIndex]->HasVisualization;
}

void AudioProcessor::ResetPlugins()
{
	for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i)
	{
		ChangePlugin(i, L"None");
		SetPluginBypassed(i, false);
		SetPluginVolumeMix(i, 1.0f);
	}
}

int AudioProcessor::ProcessAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	float* InputLPre = new float[framesPerBuffer];
	float* InputRPre = new float[framesPerBuffer];
	float* InputLPost = new float[framesPerBuffer];
	float* InputRPost = new float[framesPerBuffer];

	float* Seek = (float*)inputBuffer;
	for (int i = 0; i < framesPerBuffer; ++i)
	{
		InputLPre[i] = *(Seek++);
		InputRPre[i] = *(Seek++);
	}
	
	int PluginCount = Plugins.size();
	for (int i = 0; i < PluginCount; i++)
	{
		for (int i = 0; i < framesPerBuffer; ++i)
		{
			InputLPost[i] = InputLPre[i];
			InputRPost[i] = InputRPre[i];
		}
	
		Plugins[i]->ProcessData(InputLPost, InputRPost, framesPerBuffer);
	
		float DryWetMix = Plugins[i]->DryWetMix;
		for (int i = 0; i < framesPerBuffer; ++i)
		{
			InputLPre[i] = (DryWetMix * InputLPost[i]) + ((1 - DryWetMix) * InputLPre[i]);
			InputRPre[i] = (DryWetMix * InputRPost[i]) + ((1 - DryWetMix) * InputRPre[i]);
		}
	}
	
	Seek = (float*)outputBuffer;
	for (int i = 0; i < framesPerBuffer; ++i)
	{
		*(Seek++) = InputLPre[i] > 1.0f ? 1.0f : InputLPre[i];
		*(Seek++) = InputRPre[i] > 1.0f ? 1.0f : InputRPre[i];
	}

	delete InputLPre;
	delete InputRPre;
	delete InputLPost;
	delete InputRPost;

	return paContinue;
}
