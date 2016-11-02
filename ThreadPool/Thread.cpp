#include "Thread.h"

Thread::Thread()
{
}

void Thread::StartThread(LPTHREAD_START_ROUTINE threadsRoutine)
{
	_hThread = CreateThread(NULL, 0, threadsRoutine, NULL, 0, NULL);
}

HANDLE Thread::GetThreadHandle()
{
	return _hThread;
}

Thread::~Thread()
{
	delete _hThread;
}
