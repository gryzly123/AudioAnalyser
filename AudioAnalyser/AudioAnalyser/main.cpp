#include "PCH.h"
#include "MainWindow.h"

#define App System::Windows::Forms::Application

[System::STAThread]
void Main(array<System::String^>^ Argv)
{
	//konfiguracja wstêpna
	App::EnableVisualStyles();
	App::SetCompatibleTextRenderingDefault(false);
	AudioAnalyser::MainWindow^ MainWindowInstance = gcnew AudioAnalyser::MainWindow();

	//uruchomienie g³ównego okna
	App::Run(MainWindowInstance);

	//cleanup po zamkniêciu okna
	AudioProcessor::Shutdown();
	IoManager::Shutdown();
}
