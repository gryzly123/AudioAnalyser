#pragma once

//STD
#include <string>
#include <vector>
#include <deque>
#include <complex>

//Windows
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <vcclr.h>

//tylko wewn¹trz AudioAnalysera - pomijamy headery AA za³¹czane z RackControls
#ifndef FROM_RACK_CONTROLS

//AudioAnalyser
#include "Utilities.h"
#include "LookupTables.h"

//PortAudio
#include "portaudio.h"

//Libsndfile
#include "sndfile.h"

#endif

//ustawienia sta³e AudioAnalysera
#define GUI_RACKITEMS_COUNT 7
#define AUDIO_SAMPLERATE 44100.f
#define AUDIO_CHANNELCOUNT 2
#define AUDIO_FORMAT (SF_FORMAT_WAV | SF_FORMAT_PCM_16)

//definicje matematyczne
#define M_PI 3.14159265359f
#define M_TAU 6.28318530718f //tau = 2 * pi
#define pow2(x) (1 << x)

//globalne delegaty
public delegate System::Void WindowShutdown(System::Int32);
