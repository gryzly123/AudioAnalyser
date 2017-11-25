#include "PCH.h"
#include "VisWindow.h"
#include "VisWindowFactory.h"

using namespace SFML::Graphics;
using namespace SFML::Window;

void VisWindow::UpdateWindow()
{
	HandleEvents();
	UpdateScreen();
}

void VisWindow::HandleEvents()
{
	Window->DispatchEvents();
	//Event WindowEvent;
	//if (!Window->PollEvent(WindowEvent)) return;
	//
	//switch (WindowEvent.Type)
	//{
	//case EventType::Closed:
	//	KillWindow();
	//	break;
	//
	//case EventType::Resized:
	//	UpdateResolution(Window->Size.X, Window->Size.Y);
	//	break;
	//}
}

void VisWindow::UpdateResolution(int X, int Y)
{
	ResX = X;
	ResY = Y;
	float fx = static_cast<float>(ResX);
	float fy = static_cast<float>(ResY);
	Window->SetView(gcnew SFML::Graphics::View(FloatRect(0.f, 0.f, fx, fy)));
}

void VisWindow::KillWindow()
{
	RequestedShutdown = true;
	Window->Close();
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
	::System::Windows::Forms::MessageBox::Show("INIT");
	if (SfWindowInitialized) return;
	Window = gcnew SFML::Graphics::RenderWindow(SFML::Window::VideoMode(100, 100), "", Styles::Titlebar | Styles::Close | Styles::Resize);
	Window->SetFramerateLimit(60);
	ResX = 100;
	ResY = 100;
	SfWindowInitialized = true;
}

void VisWindow::GetResolution(int& X, int& Y)
{
	X = ResX;
	Y = ResY;
}
void VisWindow::SetTitle(String^ Title)
{
	Window->SetTitle(Title);
}
