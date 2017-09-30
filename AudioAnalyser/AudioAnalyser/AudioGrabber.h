#pragma once
#include <SFML\Audio\SoundBufferRecorder.hpp>

class AudioGrabber : public sf::SoundRecorder
{
public:
	bool WasInitialized = false;

	static AudioGrabber* GetAudioGrabber(bool ForceReinitialization = false);


private:
	AudioGrabber();
	~AudioGrabber();

	static AudioGrabber* Instance;

	//SoundRecorder interface
	virtual bool onStart() override;
	bool onProcessSamples(const short int* samples, std::size_t sampleCount);
	virtual void onStop() override;
};