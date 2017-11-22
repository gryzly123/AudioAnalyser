#include "PCH.h"
#include "VisWindowFactory.h"
#include "VisWindow.h"
#include "ClrUnmanagedMutex.h"

VisWindowManager::VisWindowManager()
{
	Register(PendingUpdatesMutex);
	SuccessfulInit = PendingUpdatesMutex == NULL ? false : true;
	if (SuccessfulInit) return;

	DialogResult Result = MessageBox::Show(L"Could not initialize visualization engine. Start AudioAnalyser without it?", L"WINAPI Error", MessageBoxButtons::YesNo);
	IgnoreModule = (Result == DialogResult::Yes);
}

VisWindowManager::~VisWindowManager()
{
	ModuleShutdownRequested = true;
	Unregister(PendingUpdatesMutex);
	Instance = nullptr;
}

VisWindowManager* VisWindowManager::Instance = nullptr;

void VisWindowManager::PushDataUpdate(const VisWindowDataUpdate& Update)
{
	PendingUpdates.push_back(Update);
}

int VisWindowManager::PushNewWindow(VisWindow* Window)
{
	Lock(PendingUpdatesMutex, LockResult);
	while (mtx2) { }
	mtx1 = true;

	DeclaredWindows.push_back(Window);
	int NewWindowIndex = DeclaredWindows.size() - 1;

	Unlock(PendingUpdatesMutex);
	mtx1 = false;

	return NewWindowIndex;
}

void VisWindowManager::WindowThreadMethod()
{
	int i = 0;
	while (!ModuleShutdownRequested /*&& i++ < 2*/)
	{
		Lock(PendingUpdatesMutex, LockResult);
		while (mtx1) { }
		mtx2 = true;

		int UpdateCount = PendingUpdates.size();
		for (int i = 0; i < UpdateCount; ++i)
		{
			VisWindowDataUpdate Update = PendingUpdates[i];
			VisWindow* Window = DeclaredWindows[Update.TargetWindow];
			if (!Window) continue;
		
			if (Update.IsConfig) Window->UpdateConfig(Update.ConfigType, Update.ConfigData);
			else
			{
				Window->UpdateContent(Update.ContentData, Update.ContentLength);
			}
		}
		PendingUpdates.clear();
		
		Unlock(PendingUpdatesMutex);
		mtx2 = false;

		int CurrentlyOpenedWindows = DeclaredWindows.size();
		bool AreAnyWindowsActive = false;
		for (int i = 0; i < CurrentlyOpenedWindows; ++i)
		{
			VisWindow* Window = DeclaredWindows[i];
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
		
		if (!AreAnyWindowsActive) DeclaredWindows.clear();

		//System::Windows::Forms::MessageBox::Show("TICC");

	}
}

VisWindowManager* VisWindowManager::GetInstance()
{
	if (!Instance) Instance = new VisWindowManager();
	return Instance;
}

VisWindow* VisWindowFactory::ConstructVisWindow(std::wstring WindowType)
{
	if (WindowType == (L"Oscilloscope")) return new OscillatorWindow();
}
