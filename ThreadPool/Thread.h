#pragma once
#include <Windows.h>
class Thread
{
public:
	Thread();
	~Thread();

	void StartThread(LPTHREAD_START_ROUTINE threadsRoutine);
	HANDLE GetThreadHandle();

private:
	HANDLE _hThread;
	LPDWORD _threadId;
};

