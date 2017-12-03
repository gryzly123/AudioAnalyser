#pragma once

//STD
#include <string>
#include <vector>

//Windows
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <vcclr.h>

//tylko wewn¹trz AudioAnalysera - pomijamy headery AA za³¹czane z RackControls
#ifndef FROM_RACK_CONTROLS

//AudioAnalyser
#include "Utilities.h"

//PortAudio
#include "portaudio.h"

//Libsndfile
#include "sndfile.h"

//SFML
#include "SFML\Graphics.hpp"

#endif

#define GUI_RACKITEMS_COUNT 7
#define AUDIO_SAMPLERATE 44100
#define AUDIO_CHANNELCOUNT 2
#define AUDIO_FORMAT (SF_FORMAT_WAV | SF_FORMAT_PCM_16)

#define ToClr(x) gcnew System::String(x.c_str())
#define Break(x) MessageBox::Show(x)

public delegate System::Void WindowShutdown(System::Int32);
