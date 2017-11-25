#pragma once
#include "PCH.h"
using namespace ::System;
using namespace ::System::Windows::Forms;
using namespace ::System::Collections::Generic;
using namespace SFML;

public ref class VisWindow
{
private:
	int ResX, ResY;
	void* ChildPtr; //do rzutowania na obiekt klasy-dziecka

	void HandleEvents(); //zarz¹dzanie zdarzeniami
	void UpdateResolution(int X, int Y); //zmiana rozdzielczoœci okna

protected:
	VisWindow();
	~VisWindow(); //niszczenie obiektu (zniszczy okno, jeœli nie zosta³o to zrobione rêcznie)
	
	SFML::Graphics::RenderWindow^ Window;

	//zarz¹dzanie oknem
	void GetResolution(int& X, int& Y); //pobranie rozdzielczoœci okna
	void SetTitle(String^ Title); //zmiana nazwy okna (domyœlnie jest pusta)

public:
	//Opcje dla VisWindowManagera
	bool SfWindowInitialized = false;
	bool RequestedShutdown = false;
	void InitWindowAsync();
	void UpdateWindow();
	void KillWindow(); //zamkniêcie okna z zewn¹trz lub z Event::Close
	
	//interfejs VisWindow
	virtual void UpdateContent(float* Data, int Length) { }
	virtual void UpdateConfig(int Type, float Data) { }
protected:
	virtual void UpdateScreen() { }

};

public ref class OscillatorWindow : public VisWindow
{
	List<Single>^ SoundData;

public:
	OscillatorWindow()
	{
		List<Single>^ SoundData = gcnew List<Single>();
	}

	virtual void UpdateContent(float* Data, int Length) override
	{
		float* Seek = Data;
		for (int i = 0; i < Length; ++i) SoundData->Add(*Seek++);
	}

	virtual void UpdateConfig(int Type, float Data) override
	{
	}

	virtual void UpdateScreen() override
	{
		//int ResX, ResY;
		//GetResolution(ResX, ResY);
		//if (SoundData.size() < ResX) return;
		//
		//Window.clear();
		//
		//for (int i = 0; i < ResX - 10; ++i)
		//{
		//	float NewVal = SoundData[0];
		//	SoundData.erase(SoundData.begin());
		//	sf::RectangleShape Line(sf::Vector2f(1, 1));
		//	Line.move(sf::Vector2f(5 + i, 500 * (NewVal + 1) / 2));
		//	Window.draw(Line);
		//}
		//
		//Window.display();
	}
};
