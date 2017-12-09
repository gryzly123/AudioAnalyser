#pragma once

//STD
#include <string>
#include <vector>
#include <complex>

//Windows
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <vcclr.h>

//tylko wewn�trz AudioAnalysera - pomijamy headery AA za��czane z RackControls
#ifndef FROM_RACK_CONTROLS

//AudioAnalyser
#include "Utilities.h"
#include "LookupTables.h"

//PortAudio
#include "portaudio.h"

//Libsndfile
#include "sndfile.h"

//SFML
#include "SFML\Graphics.hpp"

#endif

//ustawienia sta�e AudioAnalysera
#define GUI_RACKITEMS_COUNT 7
#define AUDIO_SAMPLERATE 44100.f
#define AUDIO_CHANNELCOUNT 2
#define AUDIO_FORMAT (SF_FORMAT_WAV | SF_FORMAT_PCM_16)

//definicje matematyczne
#define M_PI 3.14159265359f

//globalne delegaty
public delegate System::Void WindowShutdown(System::Int32);
