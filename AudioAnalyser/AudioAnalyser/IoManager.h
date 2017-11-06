#pragma once
#include "PCH.h"
#include "AudioProcessor.h"

struct AudioDevice
{
	std::wstring DeviceName = L"uninitialized";
	int ChannelCount = 0;
	int PaId = -1;
};

static int PaSoundCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	return AudioProcessor::GetInstance()->ProcessAudio(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags, userData);
}

class IoManager
{
private:
	//singleton
	static IoManager* Instance;

	//config
	const int InSampleRate = 44100;
	const int InBitDepth = 16;
	int InSamplesInBlock = 256;

	//portaudio
	PaStreamParameters InputParameters, OutputParameters;
	PaStream *CurrentStream;
	PaError LastPaErrorCode;
	bool PaInitialized = false, PaStarted = false;

	//wszystkie urz¹dzenia
	std::vector<AudioDevice> AudioDevicesInput;
	std::vector<AudioDevice> AudioDevicesOutput;
	int DefaultAudioInput  = -1;
	int DefaultAudioOutput = -1;
	bool NoInputDevices = false;
	bool NoOutputDevices = false;

	//wybrane urz¹dzenia
	int SelectedAudioInput = 0;
	int SelectedAudioOutput = 0;
	bool IsInputMono = false;
	bool IsOutputMono = false;

	//metody abstrakcji portaudio
	bool ThrowPaError() { return false; }

	bool InitializePortAudio()
	{
		//inicjalizacja PA
		LastPaErrorCode = Pa_Initialize();
		if (LastPaErrorCode != paNoError) return ThrowPaError();

		//przygotowanie listy urz¹dzeñ audio
		int AudioDeviceCount = Pa_GetDeviceCount();
		int DefaultInput = Pa_GetDefaultInputDevice();
		int DefaultOutput = Pa_GetDefaultOutputDevice();

		for (int i = 0; i < AudioDeviceCount; i++)
		{
			const PaDeviceInfo* DeviceInfo = Pa_GetDeviceInfo(i);
			const PaHostApiInfo* HostInfo = Pa_GetHostApiInfo(DeviceInfo->hostApi);

			if (!DeviceInfo) continue;				//pomijamy nieprawdi³owe urz¹dzenia
			if (HostInfo->type != paMME) continue;	//pomijamy interfejsy audio inne ni¿ MME

			AudioDevice NewDevice;
			NewDevice.DeviceName = Utilities::WideFromMultibyteCharArray(DeviceInfo->name);

			if (NewDevice.DeviceName.size() > 30) NewDevice.DeviceName += L"...";
			NewDevice.ChannelCount = (DeviceInfo->maxOutputChannels) ? DeviceInfo->maxOutputChannels : DeviceInfo->maxInputChannels;
			NewDevice.PaId = i;

			//odnalezienie urz¹dzeñ domyœlnych
			if (DeviceInfo->maxOutputChannels)
			{
				AudioDevicesOutput.push_back(NewDevice);
				if (i == DefaultOutput)
				{
					DefaultAudioOutput = AudioDevicesOutput.size() - 1;
				}
			}
			else
			{
				AudioDevicesInput.push_back(NewDevice);
				if (i == DefaultInput)
				{
					DefaultAudioInput = AudioDevicesInput.size() - 1;
				}
			}
		}

		SelectedAudioInput = DefaultAudioInput;
		SelectedAudioOutput = DefaultAudioOutput;

		//sprawdzamy, czy na pewno mamy jakiekolwiek urz¹dzenia
		if (!AudioDevicesInput. size()) NoInputDevices = true;
		if (!AudioDevicesOutput.size()) NoOutputDevices = true;

		return true;
	}

	bool DeinitializePortAudio()
	{
		Pa_Terminate();
	}

	bool StartPortAudio()
	{
		if (PaStarted) return true;

		if (!NoInputDevices)
		{
			InputParameters.device = AudioDevicesInput[SelectedAudioInput].PaId;
			InputParameters.channelCount = IsInputMono ? 1 : 2;
			InputParameters.sampleFormat = paFloat32;
			InputParameters.suggestedLatency = Pa_GetDeviceInfo(InputParameters.device)->defaultLowInputLatency;
			InputParameters.hostApiSpecificStreamInfo = NULL;
		}

		if (!NoOutputDevices)
		{
			OutputParameters.device = AudioDevicesOutput[SelectedAudioOutput].PaId;
			OutputParameters.channelCount = IsOutputMono ? 1 : 2;
			OutputParameters.sampleFormat = paFloat32;
			OutputParameters.suggestedLatency = Pa_GetDeviceInfo(OutputParameters.device)->defaultLowOutputLatency;
			OutputParameters.hostApiSpecificStreamInfo = NULL;
		}

		LastPaErrorCode = Pa_OpenStream(
			&CurrentStream,
			NoInputDevices  ? nullptr : &InputParameters,
			NoOutputDevices ? nullptr : &OutputParameters,
			InSampleRate,
			InSamplesInBlock * 2,
			true,
			&PaSoundCallback,
			NULL);
		if (LastPaErrorCode != paNoError) return ThrowPaError();

		LastPaErrorCode = Pa_StartStream(CurrentStream);
		if (LastPaErrorCode != paNoError) return ThrowPaError();

		PaStarted = true;
		return PaStarted;
	}

	bool StopPortAudio()
	{
		if (!PaStarted) return true;
		LastPaErrorCode = Pa_CloseStream(CurrentStream);
		PaStarted = false;
		if (LastPaErrorCode != paNoError) return ThrowPaError();
	}
	
	IoManager() { InitializePortAudio(); }
	~IoManager() { DeinitializePortAudio(); }

public:
	static IoManager* GetInstance()
	{
		if (!Instance) Instance = new IoManager();
		return Instance;
	}

	void GetCurrentConfig(int& CurrentInput, int& DefaultInput, int& CurrentOutput, int& DefaultOutput, std::vector<AudioDevice>& InputDevices, std::vector<AudioDevice>& OutputDevices, int& Blocksize)
	{
		CurrentInput  = SelectedAudioInput;
		DefaultInput  = DefaultAudioInput;
		CurrentOutput = SelectedAudioOutput;
		DefaultOutput = DefaultAudioOutput;
		InputDevices  = AudioDevicesInput;
		OutputDevices = AudioDevicesOutput;
		Blocksize = InSamplesInBlock;
	}

	void SetNewConfig(int NewInput, int NewOutput, int NewBlocksize)
	{
		if (NewInput     >= 0) SelectedAudioInput = NewInput;
		if (NewOutput    >= 0) SelectedAudioOutput = NewOutput;
		if (NewBlocksize >= 0) InSamplesInBlock = (int)pow(2, NewBlocksize + 6);

		StopPortAudio();
		StartPortAudio();
	}

	void StartProcessing() { StartPortAudio(); }
	void StopProcessing() { StopPortAudio(); }

	bool IsProcessing() { return PaStarted; }
};

