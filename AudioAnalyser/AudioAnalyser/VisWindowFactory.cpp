#include "PCH.h"
#include "VisWindowFactory.h"
#include "VisWindow.h"

VisWindowManager::VisWindowManager()
{
	//Register(PendingUpdatesMutex);
	DeclaredWindows = gcnew List<VisWindow^>();
	PendingUpdates = gcnew List<VisWindowDataUpdate^>();
}

VisWindowManager::~VisWindowManager()
{
	ModuleShutdownRequested = true;
	//Unregister(PendingUpdatesMutex);
	Instance = nullptr;
}


void VisWindowManager::PushDataUpdate(VisWindowDataUpdate^ Update)
{
	PendingUpdates->Add(Update);
}

int VisWindowManager::PushNewWindow(VisWindow^ Window)
{
	//Lock(PendingUpdatesMutex, LockResult);
	while (mtx2) { }
	mtx1 = true;

	DeclaredWindows->Add(Window);
	int NewWindowIndex = DeclaredWindows->Count - 1;

	//Unlock(PendingUpdatesMutex);
	mtx1 = false;

	return NewWindowIndex;
}

void VisWindowManager::WindowThreadMethod()
{
	int i = 0;
	while (!ModuleShutdownRequested /*&& i++ < 2*/)
	{
		//Lock(PendingUpdatesMutex, LockResult);
		while (mtx1) { }
		mtx2 = true;

		int UpdateCount = PendingUpdates->Count;
		for (int i = 0; i < UpdateCount; ++i)
		{
			VisWindowDataUpdate^ Update = PendingUpdates[i];
			VisWindow^ Window = DeclaredWindows[Update->TargetWindow];
			if (!Window) continue;
		
			if (Update->IsConfig) Window->UpdateConfig(Update->ConfigType, Update->ConfigData);
			else
			{
				Window->UpdateContent(Update->ContentData, Update->ContentLength);
			}
		}
		PendingUpdates->Clear();
		
		//Unlock(PendingUpdatesMutex);
		mtx2 = false;

		int CurrentlyOpenedWindows = DeclaredWindows->Count;
		bool AreAnyWindowsActive = false;
		for (int i = 0; i < CurrentlyOpenedWindows; ++i)
		{
			VisWindow^ Window = DeclaredWindows[i];
			if (!Window) continue;
		
			AreAnyWindowsActive = true;
			if (!Window->SfWindowInitialized) { Window->InitWindowAsync(); }
			Window->UpdateWindow();
			if (Window->RequestedShutdown)
			{
				Window->KillWindow();
				delete Window;
				DeclaredWindows[i] = nullptr;
			}
		}
		
		if (!AreAnyWindowsActive) DeclaredWindows->Clear();

		//System::Windows::Forms::MessageBox::Show("TICC");

	}
}

VisWindowManager^ VisWindowManager::GetInstance()
{
	if (!Instance) Instance = gcnew VisWindowManager();
	return Instance;
}

VisWindow^ VisWindowFactory::ConstructVisWindow(std::wstring WindowType)
{
	if (WindowType == (L"Oscilloscope")) return gcnew OscillatorWindow();
}

void VisWindowManager::WindowThreadMethodStatic()
{
	VisWindowManager^ Inst = GetInstance();
	if (Inst->ThreadActive) return;

	Inst->ThreadActive = true;
	Inst->WindowThreadMethod();
	Inst->ThreadActive = false;
}
