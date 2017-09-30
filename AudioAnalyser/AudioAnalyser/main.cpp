#include "MainWindow.h"
#define App System::Windows::Forms::Application

[System::STAThread]
void Main(array<System::String^>^ Argv)
{
	App::EnableVisualStyles();
	App::SetCompatibleTextRenderingDefault(false);

	first_clr::MainWindow Form;
	App::Run(%Form);
}