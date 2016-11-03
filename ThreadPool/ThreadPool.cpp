#include "ThreadPool.h"

ThreadPool::ThreadPool(int numberOfThreads)
{
	_logger = new Logger("log.txt");
	_threads = new Thread[numberOfThreads];
	_logger->LogThreadPoolInitialization(numberOfThreads);

    _numberOfThreads = numberOfThreads;
}

void ThreadPool::AddNewTask(LPTHREAD_START_ROUTINE threadRoutine, std::queue<LPTHREAD_START_ROUTINE> *tasks)
{
	int freeThreadIndex = GetFreeThreadIndex();
	
	if (freeThreadIndex == -1)
	{
		tasks->push(threadRoutine);
		_logger->LogThreadPoolIsFilled();
	}
	else
	{
		_threads[freeThreadIndex].StartThread(threadRoutine);
		_logger->LogTaskAdding((int)_threads[freeThreadIndex].GetThreadHandle());
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

bool ThreadPool::isFullyCompleted()
{	
	for (int i = 0; i < _numberOfThreads; i++)
	{
		if (!isAvailable(&_threads[i]))
		{
			return false;
		}
	}

	return true;
}

ThreadPool::~ThreadPool()
{
	delete _threads; 
}
