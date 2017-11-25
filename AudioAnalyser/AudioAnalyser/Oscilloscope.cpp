#include "PCH.h"
#include "DspPlugin.h"
#include "VisWindowFactory.h"

void Oscilloscope::ProcessData(float* BufferL, float* BufferR, int Length)
{
	if (VisWindowIndex >= 0)
	{
		VisWindowDataUpdate^ Update = gcnew(VisWindowDataUpdate);
		Update->IsConfig = false;
		Update->TargetWindow = VisWindowIndex;
		Update->ContentLength = Length;
		Update->ContentData = new float[Length];
		for (int i = 0; i < Length; ++i) Update->ContentData[i] = BufferL[i];
		VisWindowManager::GetInstance()->PushDataUpdate(Update);
	}
	else
	{
		VisWindow^ Window = VisWindowFactory::ConstructVisWindow(L"Oscilloscope");
		VisWindowIndex = VisWindowManager::GetInstance()->PushNewWindow(Window);
	}
}