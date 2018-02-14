#include "PCH.h"
#include "AudioProcessor.h"
#include "DspPlugin.h"
#include "IoManager.h"

#pragma managed(push, off)
AudioProcessor* AudioProcessor::Instance = nullptr;

AudioProcessor::AudioProcessor()
{
	for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i) Plugins.push_back(new NullPlugin());
}

AudioProcessor::~AudioProcessor()
{
	for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i) delete Plugins[i];
	Instance = nullptr;
}

DspPlugin* AudioProcessor::PluginFactory(std::wstring NewPluginName)
{
	if (NewPluginName == (L"None")) return new NullPlugin();
	if (NewPluginName == (L"(none)")) return new NullPlugin();

	if (NewPluginName == (L"Sine Wave")) return new SineWaveGenerator();
	if (NewPluginName == (L"Saw Wave")) return new SawWaveGenerator();
	if (NewPluginName == (L"Square Wave")) return new SquareWaveGenerator();
	if (NewPluginName == (L"White noise")) return new WhiteNoiseGenerator();

	if (NewPluginName == (L"Oscilloscope")) return new Oscilloscope();
	if (NewPluginName == (L"Spectrum")) return new Spectrum();
	if (NewPluginName == (L"Spectrogram")) return new Spectrogram();
	
	if (NewPluginName == (L"Gain")) return new LinearAmplifier();
	if (NewPluginName == (L"Clip")) return new Clip();
	if (NewPluginName == (L"Phase Inverter")) return new PhaseInverter();
	
	if (NewPluginName == (L"Bitcrusher")) return new Bitcrusher();
	if (NewPluginName == (L"Decimator")) return new Decimator();

	if (NewPluginName == (L"Panner")) return new Panner();
	if (NewPluginName == (L"Stereo Merger")) return new StereoMerger();
	if (NewPluginName == (L"Stereo to Mid-Side")) return new StereoToMidside();
	if (NewPluginName == (L"Low Pass Filter (avg)")) return new LowpassFilterAvg();
	if (NewPluginName == (L"Low Pass Filter (sinc)")) return new LowPassFilterSinc();

	if (NewPluginName == (L"Retrigger (Simple)")) return new RetriggerSimple();
	if (NewPluginName == (L"Retrigger")) return new Retrigger();
	if (NewPluginName == (L"Reverser (Simple)")) return new ReverserSimple();
	if (NewPluginName == (L"Reverser")) return new Reverser();

	Utilities::ShowMessagebox(NewPluginName + L" was not found. Using null");
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

#pragma managed(push, on)
void AudioProcessor::AskPluginForRedraw(int AtIndex, System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImgPtr, int Width, int Height, bool FirstFrame)
{
	Plugins[AtIndex]->UpdatePictureBox(Image, ImgPtr, Width, Height, FirstFrame);
}
#pragma managed(push, off)


void AudioProcessor::UpdatePluginParameterByIndex(int PluginIndex, int AtIndex, float NewValue)
{
	DspPluginParameter* Param = Plugins[PluginIndex]->GetParameters()[AtIndex];
	Param->CurrentValue = NewValue;
}

void AudioProcessor::UpdatePluginParameterByName(int PluginIndex, std::wstring AtName, float NewValue)
{
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
	HasConfig = Plugins[AtIndex]->GetParameters().size() > 0;
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
	IsBusy = true;
	
	const int Samplecount = 2 * framesPerBuffer;
	const int FramesPerBuffer = (int)framesPerBuffer;
	
	InputSource IS; OutputSource OS;
	IoManager* IM = IoManager::GetInstance();
	IM->GetCurrentSources(IS, OS);

	float* InputLPre = new float[framesPerBuffer];
	float* InputRPre = new float[framesPerBuffer];
	float* InputLPost = new float[framesPerBuffer];
	float* InputRPost = new float[framesPerBuffer];
	switch (IS)
	{
	case InputSource::IS_Stream: //nie rób nic, próbki s¹ ju¿ w buforze
		break;

	case InputSource::IS_None: //wyzeruj próbki (efekt wy³¹czenia wejœcia)
		for (int i = 0; i < Samplecount; ++i) ((float*)inputBuffer)[i] = 0.0f;
		break;

	case InputSource::IS_File: //podmieñ próbki ze strumienia na próbki z pliku
		IM->GetSamplesFromInputFile((float*)inputBuffer);
		break;
	}

	float* Seek = (float*)inputBuffer;
	for (int  i = 0; i < FramesPerBuffer; ++i)
	{
		InputLPre[i] = *(Seek++);
		InputRPre[i] = *(Seek++);
	}

	int PluginCount = Plugins.size();
	for (int i = 0; i < PluginCount; i++)
	{
		if (Plugins[i]->Bypass && !Plugins[i]->HasVisualization) continue;

		for (int i = 0; i < FramesPerBuffer; ++i)
		{
			InputLPost[i] = InputLPre[i];
			InputRPost[i] = InputRPre[i];
		}

		Plugins[i]->ProcessData(InputLPost, InputRPost, framesPerBuffer);

		float DryWetMix = Plugins[i]->DryWetMix;
		for (int i = 0; i < FramesPerBuffer; ++i)
		{
			InputLPre[i] = (DryWetMix * InputLPost[i]) + ((1 - DryWetMix) * InputLPre[i]);
			InputRPre[i] = (DryWetMix * InputRPost[i]) + ((1 - DryWetMix) * InputRPre[i]);
		}
	}

	Seek = (float*)outputBuffer;
	for (int i = 0; i < FramesPerBuffer; ++i)
	{
		*(Seek++) = InputLPre[i] > 1.0f ? 1.0f : InputLPre[i];
		*(Seek++) = InputRPre[i] > 1.0f ? 1.0f : InputRPre[i];
	}

	switch (OS)
	{
	case OutputSource::OS_Stream:
		break; //nie rób nic, próbki s¹ ju¿ w buforze

	case OutputSource::OS_File: //skopiuj próbki do pliku
	case OutputSource::OS_Both:
		IM->AppendSamplesToOutputFile((float*)outputBuffer);
		if (OS == OutputSource::OS_Both) break; //jeœli dzia³a tylko plik, przejdŸ do zerowania

	case InputSource::IS_None: //wyzeruj próbki (efekt wy³¹czenia wyjœcia)
		for (int i = 0; i < Samplecount; ++i) ((float*)outputBuffer)[i] = 0.0f;
		break;
	}

	delete InputLPre;
	delete InputRPre;
	delete InputLPost;
	delete InputRPost;

	IsBusy = false;
	return paContinue;
}
