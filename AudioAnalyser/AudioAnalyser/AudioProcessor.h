#pragma once
#include "DspPlugin.h"
#include "portaudio.h"
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

	AudioProcessor();
	~AudioProcessor();
	DspPlugin* PluginFactory(std::wstring NewPluginName);

public:
	static AudioProcessor* GetInstance();
	void ChangePlugin(int AtIndex, const std::wstring NewPluginName);
	void SwapPlugins(int AtIndex, PluginSwapDirection Direction);
	void ChangePluginVolumeMix(int AtIndex, float Value);
	std::vector<DspPluginParameter*> GetPluginParameters(int AtIndex);
	void UpdatePluginParameter(int PluginIndex, int AtIndex, float NewValue);
	std::wstring GetPluginName(int AtIndex);
	int ProcessAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
};
