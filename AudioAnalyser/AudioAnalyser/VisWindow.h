#pragma once
#include "PCH.h"

using namespace System::Windows::Forms;
class VisWindow;
struct VisWindowDataUpdate;

class VisWindow
{
	friend class VisWindowManager;

private:
	int ResX, ResY;
	bool RequestedShutdown = false;
	bool SfWindowInitialized = false;
	void* ChildPtr; //do rzutowania na obiekt klasy-dziecka

	void InitWindowAsync();
	void UpdateWindow();
	void HandleEvents(); //zarz¹dzanie zdarzeniami
	void UpdateResolution(int X, int Y); //zmiana rozdzielczoœci okna
	void KillWindow(); //zamkniêcie okna z zewn¹trz lub z Event::Close

protected:
	VisWindow();
	~VisWindow(); //niszczenie obiektu (zniszczy okno, jeœli nie zosta³o to zrobione rêcznie)
	
	sf::RenderWindow* Window;

	//zarz¹dzanie oknem
	void GetResolution(int& X, int& Y); //pobranie rozdzielczoœci okna
	void SetTitle(sf::String Title); //zmiana nazwy okna (domyœlnie jest pusta)

public:
	//interfejs VisWindow
	virtual void UpdateContent(float* Data, int Length) = 0;
	virtual void UpdateConfig(int Type, float Data) = 0;
protected:
	virtual void UpdateScreen() = 0;

};

class OscillatorWindow : public VisWindow
{
	std::vector<float> SoundData;

public:
	OscillatorWindow() { }

	virtual void UpdateContent(float* Data, int Length) override
	{
		float* Seek = Data;
		for (int i = 0; i < Length; ++i) SoundData.push_back(*Seek++);
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
