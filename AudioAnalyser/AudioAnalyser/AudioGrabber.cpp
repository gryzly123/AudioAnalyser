#include "AudioGrabber.h"

AudioGrabber* AudioGrabber::GetAudioGrabber(bool ForceReinitialization)
{
	if (Instance == nullptr) Instance = new AudioGrabber();
	else if (ForceReinitialization)
	{
		delete Instance; //stop() wywo³a siê przy usuniêciu
		Instance = new AudioGrabber();
	}
	return Instance;
}


AudioGrabber::AudioGrabber()
{
	if (sf::SoundBufferRecorder::isAvailable())
	{
		std::vector<std::string> ListOfDevices = sf::SoundBufferRecorder::getAvailableDevices();
		int Count = ListOfDevices.size();

		int SelectedDevice = 1;
		if (!SelectedDevice || SelectedDevice > Count) SelectedDevice = 1;

		this->setDevice(ListOfDevices[SelectedDevice - 1]);
		this->setChannelCount(1);
	}
	WasInitialized = this->start();
}

AudioGrabber::~AudioGrabber()
{
	this->stop();
}

AudioGrabber* AudioGrabber::Instance;

//SoundRecorder interface
bool AudioGrabber::onStart()
{
	return true;
}

bool AudioGrabber::onProcessSamples(const short int* samples, std::size_t sampleCount)
{
	int* Data = new int[sampleCount];
	memcpy(Data, samples, sampleCount);

	return true;
}


void AudioGrabber::onStop()
{

}
