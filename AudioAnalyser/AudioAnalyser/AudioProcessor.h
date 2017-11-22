#pragma once
#include "PCH.h"
class DspPlugin;
struct DspPluginParameter;

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
	bool IsBusy = false;

public:
	static AudioProcessor* GetInstance();
	int ProcessAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
	bool GetIsBusy() { return IsBusy; }
	
	void ChangePlugin(int AtIndex, const std::wstring NewPluginName);
	void SwapPlugins(int AtIndex, PluginSwapDirection Direction);
	void ResetPlugins();
	
	std::wstring GetPluginName(int AtIndex);
	void GetPluginWindowCapabilities(int AtIndex, bool& HasConfig, bool& HasVis);
	void SetPluginVolumeMix(int AtIndex, float Value);
	float GetPluginVolumeMix(int AtIndex);
	std::vector<DspPluginParameter*> GetPluginParameters(int AtIndex);
	void UpdatePluginParameterByIndex(int PluginIndex, int AtIndex, float NewValue);
	void UpdatePluginParameterByName(int PluginIndex, std::wstring AtName, float NewValue);
	bool IsPluginBypassed(int AtIndex);
	void SetPluginBypassed(int AtIndex);
	void SetPluginBypassed(int AtIndex, bool NewBypassed);
	void SetPluginSolo(int AtIndex);
};
