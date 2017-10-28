#include "AudioProcessor.h"
#include "Utilities.h"

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
	Utilities::ShowMessageboxDebugonly(NewPluginName);
	if (NewPluginName == (L"Gain")) return new LinearAmplifier();
	if (NewPluginName == (L"Sine wave")) return new SineWaveGenerator();
	if (NewPluginName == (L"Retrigger (Simple)")) return new RetriggerSimple();
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
	Plugins[AtIndex] = new NullPlugin();
	delete Temp;
	Plugins[AtIndex] = PluginFactory(NewPluginName);
}

void AudioProcessor::SwapPlugins(int AtIndex, PluginSwapDirection Direction)
{
	int Id1 = AtIndex;
	int Id2 = !!Direction ? AtIndex - 1 : AtIndex + 1;

	DspPlugin* SwapHelper = Plugins[Id1];
	Plugins[Id1] = Plugins[Id2];
	Plugins[Id2] = SwapHelper;
}

void AudioProcessor::ChangePluginVolumeMix(int AtIndex, float Value)
{
	Plugins[AtIndex]->DryWetMix = Value;
}

std::vector<DspPluginParameter*> AudioProcessor::GetPluginParameters(int AtIndex)
{
	return Plugins[AtIndex]->GetParameters();
}

void AudioProcessor::UpdatePluginParameter(int PluginIndex, int AtIndex, float NewValue)
{
	DspPluginParameter* Param = Plugins[PluginIndex]->GetParameters()[AtIndex];
	Param->CurrentValue = NewValue;
}

std::wstring AudioProcessor::GetPluginName(int AtIndex)
{
	return Plugins[AtIndex]->PluginName;
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
		*(Seek++) = InputLPre[i];
		*(Seek++) = InputRPre[i];
	}

	delete InputLPre;
	delete InputRPre;
	delete InputLPost;
	delete InputRPost;

	return paContinue;
}
