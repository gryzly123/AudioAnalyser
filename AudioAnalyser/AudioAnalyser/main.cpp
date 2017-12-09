#include "PCH.h"
#include "MainWindow.h"

#define App System::Windows::Forms::Application

[System::STAThread]
void Main(array<System::String^>^ Argv)
{
	//konfiguracja wst�pna
	App::EnableVisualStyles();
	App::SetCompatibleTextRenderingDefault(false);
	AudioAnalyser::MainWindow^ MainWindowInstance = gcnew AudioAnalyser::MainWindow();

	//uruchomienie g��wnego okna
	App::Run(MainWindowInstance);

	//cleanup po zamkni�ciu okna
	AudioProcessor::Shutdown();
	IoManager::Shutdown();
}
