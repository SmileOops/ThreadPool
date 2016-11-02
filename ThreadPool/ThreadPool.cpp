#include "ThreadPool.h"

ThreadPool::ThreadPool(int numberOfThreads)
{
	_threads = new Thread[numberOfThreads];
    _numberOfThreads = _numberOfFreeThreads = numberOfThreads;
}

void ThreadPool::AddNewTask(LPTHREAD_START_ROUTINE threadsRoutine, std::queue<LPTHREAD_START_ROUTINE> *tasks)
{
	int kek = GetFreeThreadIndex();
	
	if (kek == -1)
	{
		tasks->push(threadsRoutine);
	}
	else
	{
		_threads[kek].StartThread(threadsRoutine);
		_numberOfFreeThreads--;
	}
}

int ThreadPool::GetFreeThreadIndex()
{
	for (int i = 0; i < _numberOfThreads; i++)
	{
		if (isAvailable(&_threads[i]))
		{
			return i;
		}
	}
	return -1;
}

int ThreadPool::GetFreeThreadsCount()
{
	return _numberOfFreeThreads;
}

bool ThreadPool::isAvailable(Thread *thread)
{
	DWORD status;
	
	GetExitCodeThread(thread->GetThreadHandle(), &status);
	return !isStillActive(thread, status);
}

bool ThreadPool::isStillActive(Thread *thread, DWORD status)
{
	if (status == STILL_ACTIVE)
		return true;

	TerminateThread(thread->GetThreadHandle(), 0);
	
	return false;
}

ThreadPool::~ThreadPool()
{
	delete _threads; 
}
