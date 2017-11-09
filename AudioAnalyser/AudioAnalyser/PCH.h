#pragma once

//STD
#include <string>
#include <vector>

//Windows
#include <Windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

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
#define ToCli(x) gcnew System::String(x.c_str())
#define Break(x) MessageBox::Show(x)