#pragma once
#include "PCH.h"
#include "VisWindow.h"
using namespace ::System::Collections::Generic;

public ref struct VisWindowDataUpdate
{
	bool IsConfig = false;
	int TargetWindow = -1;

	int ConfigType = 0;
	float ConfigData = 0.0f;

	int ContentLength = 0;
	float* ContentData = nullptr;

	~VisWindowDataUpdate()
	{
		if (!IsConfig) delete[] ContentData;
	}
};

public ref class VisWindowManager
{
private:
	List<VisWindow^>^ DeclaredWindows;
	List<VisWindowDataUpdate^>^ PendingUpdates;
	bool ModuleShutdownRequested = false;
	bool SuccessfulInit = false;
	bool IgnoreModule = false;
	bool mtx1 = false;
	bool mtx2 = false;
	void WindowThreadMethod();
	bool ThreadActive = false;

	VisWindowManager();
	~VisWindowManager();

public:

	static property VisWindowManager^ Instance;
	static VisWindowManager^ GetInstance();
	static void WindowThreadMethodStatic();
	int PushNewWindow(VisWindow^ Window);
	void PushDataUpdate(VisWindowDataUpdate^ Update);
};

public ref class VisWindowFactory
{
public:
	static VisWindow^ ConstructVisWindow(std::wstring WindowType);
};
