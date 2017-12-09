#pragma once
#include "PCH.h"
#include "AudioProcessor.h"
#include "SoundFile.h"

struct AudioDevice
{
	std::wstring DeviceName = L"uninitialized";
	int ChannelCount = 0;
	int PaId = -1;
};

enum InputSource
{
	IS_None = 1,
	IS_Stream = 2,
	IS_File = 3
};

enum OutputSource
{
	OS_None = 1,
	OS_Stream = 2,
	OS_File = 3,
	OS_Both = 4
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
	public: const int InSampleRate = AUDIO_SAMPLERATE;
	private: int InSamplesInBlock = 256;

	//portaudio
	PaStreamParameters InputParameters, OutputParameters;
	PaStream* CurrentStream;
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

	//pliki audio
	InSoundFile* CurrentInFile = nullptr;
	OutSoundFile* CurrentOutFile = nullptr;
	std::wstring OutFilesWorkingFolder;
	std::wstring OutFilesPrefix;

	//sesja audio
	InputSource CurrentInput = IS_None;
	OutputSource CurrentOutput = OS_None;

	//metody abstrakcji portaudio
	bool ThrowPaError()
	{
		Utilities::ShowMessagebox
		(
			Utilities::WideFromMultibyteCharArray
			(
				Pa_GetErrorText(LastPaErrorCode)
			)
		);
		return false;
	}

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
		return Pa_Terminate() == paNoError;
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
			InSamplesInBlock,
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
		while (AudioProcessor::GetInstance()->GetIsBusy()) { }
		LastPaErrorCode = Pa_CloseStream(CurrentStream);
		PaStarted = false;
		if (LastPaErrorCode != paNoError) return ThrowPaError();
	}
	
	IoManager() { InitializePortAudio(); }
	~IoManager()
	{
		DeinitializePortAudio();
		if (CurrentInFile) delete CurrentInFile;
		if (CurrentOutFile) delete CurrentOutFile;
		Instance = nullptr;
	}

public:
	static IoManager* GetInstance()
	{
		if (!Instance) Instance = new IoManager();
		return Instance;
	}
	static void Shutdown() { delete GetInstance(); }

	//konfiguracja PortAudio
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
	void SetNewConfig(int NewInput, int NewOutput, int NewBlocksize, bool StartNow = false)
	{
		bool WasRunning = PaStarted;
		StopPortAudio();

		if (NewInput >= 0) SelectedAudioInput = NewInput;
		if (NewOutput >= 0) SelectedAudioOutput = NewOutput;
		if (NewBlocksize >= 0) InSamplesInBlock = (int)pow(2, NewBlocksize + 6);
		
		if (StartNow || WasRunning) StartPortAudio();
	}
	
	//konfiguracja Ÿróde³
	InputSource SetInputSource(InputSource NewTargetSource)
	{
		int Direction = NewTargetSource + (10 * CurrentInput);
		switch (Direction)
		{
		case 11: //None->None
		case 21: //Stream->None
		case 31: //File->None
		case 22: //Stream->Stream
		case 33: //File->File
			CurrentInput = IS_None;
			break;

		case 32: //File->Stream
		case 12: //None->Stream
			CurrentInput = IS_Stream;
			break;

		case 13: //None->File
		case 23: //Stream->File
			CurrentInput = IS_File;
			break;
		}
		return CurrentInput;
	}
	OutputSource SetOutputSource(OutputSource NewTargetSource)
	{
		int Direction = NewTargetSource + (10 * CurrentOutput);
		switch (Direction)
		{
		case 11: //None->None
			break;

		case 12: //None->Stream
			CurrentOutput = OS_Stream;
			break;

		case 13: //None->File
			if(CreateNewOutputFile()) CurrentOutput = OS_File;
			else Utilities::ShowMessagebox("Output file could not be created.");
			break;

		case 21: //Stream->None
		case 22: //Stream->Stream
			CurrentOutput = OS_None;
			break;

		case 23: //Stream->File
			CurrentOutput = OS_Both;
			if (CreateNewOutputFile()) CurrentOutput = OS_Both;
			else Utilities::ShowMessagebox("Output file could not be created.");
			break;

		case 32: //File->Stream
			CurrentOutput = OS_Both;
			break;

		case 31: //File->None
		case 33: //File->File
		case 41: //Both->None
			CurrentOutput = OS_None;
			FinalizeOutputFile();
			break;

		case 42: //Both->Stream
			CurrentOutput = OS_File;
			break;

		case 43: //Both->File
			CurrentOutput = OS_Stream;
			FinalizeOutputFile();
			break;
		}

		return CurrentOutput;
	}
	void GetCurrentSources(InputSource& IS, OutputSource& OS)
	{
		IS = CurrentInput;
		OS = CurrentOutput;
	}
	
	void StartProcessing() { StartPortAudio(); }
	void StopProcessing()
	{
		StopPortAudio();
		SetInputSource(IS_None);
		SetOutputSource(OS_None);
	}
	bool IsProcessing() { return PaStarted; }

	//obs³uga plików wejœciowych Libsndfile
	bool OpenNewInputFile(std::wstring Path)
	{
		if (CurrentInFile)
		{
			delete CurrentInFile;
			CurrentInFile = nullptr;
		}
		CurrentInFile = new InSoundFile(Path);

		if (!CurrentInFile->GetFileInfo().FileOk)
		{
			delete CurrentInFile;
			return false;
		}
		return true;
	}
	bool GetSamplesFromInputFile(float* Samples)
	{
		int TargetLength = 2 * InSamplesInBlock;
		if (!CurrentInFile)
		{
			for (int i = 0; i < TargetLength; ++i) Samples[i] = 0.0f;
			return false;
		}

		CurrentInFile->ProcessData(Samples, TargetLength);
		return true;
	}
	bool GetInputFilePosition(int& InSamples, int& InSeconds, int& TotalSamples, int& TotalSeconds)
	{
		if (!CurrentInFile)
		{
			InSamples	 = 0;
			InSeconds	 = 0;
			TotalSamples = 0;
			TotalSeconds = 0;
			return false;
		}
		else
		{
			InSamples = CurrentInFile->GetFilePosition();
			TotalSamples = CurrentInFile->GetFileInfo().Length;
			InSeconds = InSamples / CurrentInFile->GetFileInfo().SampleRate;
			TotalSeconds = TotalSamples / CurrentInFile->GetFileInfo().SampleRate;
		}
		return true;
	}
	void SetInputFilePosition(int ToSeconds)
	{
		CurrentInFile->SeekFile((float)ToSeconds);
	}

	//obs³uga plików wyjœciowych Libsndfile
	void SetOutFilesWorkingFolder(std::wstring Folder) { OutFilesWorkingFolder = Folder; }
	void SetOutFilesPrefix(std::wstring Prefix) { OutFilesPrefix = Prefix; }
	bool CreateNewOutputFile()
	{
		System::DateTime^ Now = System::DateTime::Now;
		System::String^ FileFormat = L"wav";
		System::String^ FileName =
			Utilities::SystemStringFromWide(OutFilesPrefix) + " ("
			+ Now->Year.ToString("0000") + "."
			+ Now->Month.ToString("00")  + "."
			+ Now->Day.ToString("00")    + " "
			+ Now->Hour.ToString("00")   + "-"
			+ Now->Minute.ToString("00") + "-"
			+ Now->Second.ToString("00") + ")."
			+ FileFormat;

		std::wstring FullPath = OutFilesWorkingFolder + L"\\" + Utilities::WideFromSystemString(FileName);
		CurrentOutFile = new OutSoundFile(FullPath, SFF_WAV);
		return CurrentOutFile->IsFileValid();
	}
	bool AppendSamplesToOutputFile(float* Samples)
	{
		if (!CurrentOutFile) return false;

		int TargetLength = 2 * InSamplesInBlock;
		CurrentOutFile->ProcessData(Samples, TargetLength);
		return true;
	}
	void FinalizeOutputFile()
	{
		delete CurrentOutFile;
		CurrentOutFile = nullptr;
	}

	const AudioFileInfo GetInputFileDetails()
	{
		AudioFileInfo Result;
		if (CurrentInFile) Result = CurrentInFile->GetFileInfo();
		return Result;
	}
};
