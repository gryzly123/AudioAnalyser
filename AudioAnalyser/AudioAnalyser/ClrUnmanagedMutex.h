#pragma once
#define Mutex HANDLE
#define Register(x) x = CreateMutexW(NULL, FALSE, NULL);
#define Unregister(x) ReleaseMutex(x);
#define Lock(x, LockResult) DWORD LockResult = WaitForSingleObject(x, INFINITE);
#define Unlock(x) CloseHandle(x);