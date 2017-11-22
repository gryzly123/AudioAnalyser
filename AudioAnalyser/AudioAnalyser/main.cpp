#include "PCH.h"
#include "MainWindow.h"
#include "VisWindowFactory.h"
#define App System::Windows::Forms::Application

public class VisThread
{
public:
	static void DoWork()
	{
		VisWindowManager::GetInstance()->WindowThreadMethod();
	}
};


[System::STAThread]
void Main(array<System::String^>^ Argv)
{
	App::EnableVisualStyles();
	App::SetCompatibleTextRenderingDefault(false);

	VisWindowManager::GetInstance();
	System::Threading::Thread^ VisThr = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(VisThread::DoWork));
	VisThr->Start();

	AudioAnalyser::MainWindow^ MainWindowInstance = gcnew AudioAnalyser::MainWindow();
	App::Run(MainWindowInstance);
}

