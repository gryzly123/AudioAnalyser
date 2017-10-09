#include "MainWindow.h"
#define App System::Windows::Forms::Application

[System::STAThread]
void Main(array<System::String^>^ Argv)
{
	App::EnableVisualStyles();
	App::SetCompatibleTextRenderingDefault(false);

	AudioAnalyser::MainWindow MainWindowInstance;
	App::Run(%MainWindowInstance);
}