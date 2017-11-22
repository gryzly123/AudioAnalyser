#include "PCH.h"
#include "VisWindow.h"
#include "VisWindowFactory.h"

using namespace System::Windows::Forms;

void VisWindow::UpdateWindow()
{
	HandleEvents();
	UpdateScreen();
}

void VisWindow::HandleEvents()
{
	sf::Event WindowEvent;
	if (!Window->pollEvent(WindowEvent)) return;

	switch (WindowEvent.type)
	{
	case sf::Event::Closed:
		KillWindow();
		break;

	case sf::Event::Resized:
		UpdateResolution(Window->getSize().x, Window->getSize().y);
		break;
	}
}

void VisWindow::UpdateResolution(int X, int Y)
{
	ResX = X;
	ResY = Y;
	float fx = static_cast<float>(ResX);
	float fy = static_cast<float>(ResY);
	Window->setView(sf::View(sf::FloatRect(0.f, 0.f, fx, fy)));
}

void VisWindow::KillWindow()
{
	RequestedShutdown = true;
	Window->close();
}

VisWindow::~VisWindow()
{
	if (!RequestedShutdown) KillWindow();
}

VisWindow::VisWindow()
{
	
}

void VisWindow::InitWindowAsync()
{
	System::Windows::Forms::MessageBox::Show("INIT");
	if (SfWindowInitialized) return;
	Window = new sf::RenderWindow(sf::VideoMode(100, 100), "", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	Window->setFramerateLimit(60);
	ResX = 100;
	ResY = 100;
	SfWindowInitialized = true;
}

void VisWindow::GetResolution(int& X, int& Y)
{
	X = ResX;
	Y = ResY;
}
void VisWindow::SetTitle(sf::String Title)
{
	Window->setTitle(Title);
}
