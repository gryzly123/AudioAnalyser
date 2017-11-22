#pragma once
#include "PCH.h"
class VisWindow;

struct VisWindowDataUpdate
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

class VisWindowManager
{
	friend class VisThread;
private:
	VisWindowManager();
	~VisWindowManager();

	static VisWindowManager* Instance;
	std::vector<VisWindow*> DeclaredWindows;
	std::vector<VisWindowDataUpdate> PendingUpdates;
	bool ModuleShutdownRequested = false;
	bool SuccessfulInit = false;
	bool IgnoreModule = false;
	HANDLE PendingUpdatesMutex;
	bool mtx1 = false;
	bool mtx2 = false;

	void WindowThreadMethod();

public:
	static VisWindowManager* GetInstance();
	int PushNewWindow(VisWindow* Window);
	void PushDataUpdate(const VisWindowDataUpdate& Update);
};

class VisWindowFactory
{
public:
	static VisWindow* ConstructVisWindow(std::wstring WindowType);
};
