#pragma once
#include "DspPlugin.h"
#include "portaudio.h"
//#include <mutex>
#include <msclr/lock.h>

#define GUI_RACKITEMS_COUNT 7

enum PluginSwapDirection
{
	MoveUpInRack = 0,
	MoveDownInRack = 1
};

class AudioProcessor
{
private:
	std::vector<DspPlugin*> Plugins;
	static AudioProcessor* Instance;
	//std::mutex ListEditingAndProcessingLock;
	
	AudioProcessor()
	{
		for(int i = 0; i < GUI_RACKITEMS_COUNT; ++i) Plugins.push_back(new NullPlugin());
	}

	~AudioProcessor()
	{
		for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i) delete Plugins[i];
	}

	DspPlugin* PluginFactory(std::wstring NewPluginName)
	{
		if (NewPluginName.compare(L"Gain")) return new LinearAmplifier();
		if (NewPluginName.compare(L"Sine wave")) return new SineWaveGenerator();
		return new NullPlugin();
	}

public:
	static AudioProcessor* GetInstance()
	{
		if (!Instance) Instance = new AudioProcessor();
		return Instance;
	}

	void ChangePlugin(int AtIndex, const std::wstring NewPluginName)
	{
		//ListEditingAndProcessingLock.lock();

		delete Plugins[AtIndex];
		Plugins[AtIndex] = PluginFactory(NewPluginName);

		//ListEditingAndProcessingLock.unlock();
	}

	void SwapPlugins(int AtIndex, PluginSwapDirection Direction)
	{
		//ListEditingAndProcessingLock.lock();

		int Id1 = AtIndex;
		int Id2 = !!Direction ? AtIndex - 1 : AtIndex + 1;

		DspPlugin* SwapHelper = Plugins[Id1];
		Plugins[Id1] = Plugins[Id2];
		Plugins[Id2] = SwapHelper;

		//ListEditingAndProcessingLock.unlock();
	}

	int ProcessAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
	{
		//ListEditingAndProcessingLock.lock();

		float* InputL = new float[framesPerBuffer / 2];
		float* InputR = new float[framesPerBuffer / 2];
		float* Seek = (float*)inputBuffer;
		for (int i = 0; i < framesPerBuffer; i++)
		{
			InputL[i / 2] = *(Seek++);
			InputR[i / 2] = *(Seek++);
		}

		int PluginCount = Plugins.size();
		for (int i = 0; i < PluginCount; i++) Plugins[i]->ProcessData(InputL, InputR, framesPerBuffer / 2);

		Seek = (float*)outputBuffer;
		for (int i = 0; i < framesPerBuffer; i++)
		{
			*(Seek++) = InputL[i / 2];
			*(Seek++) = InputR[i / 2];
		}

		delete InputL;
		delete InputR;

		return paContinue;

		//ListEditingAndProcessingLock.unlock();
	}

};