#include "ThreadPool.h"

ThreadPool::ThreadPool(int numberOfThreads)
{
	_logger = new Logger("log.txt");
	_threads = new Thread[numberOfThreads];
	_tasks = new std::queue<LPTHREAD_START_ROUTINE>;
	_logger->LogThreadPoolInitialization(numberOfThreads);

    _numberOfThreads = numberOfThreads;
}

void ThreadPool::AddNewTask(LPTHREAD_START_ROUTINE threadRoutine)
{
	_tasks->push(threadRoutine);
}

void ThreadPool::StartExecutingTasks()
{
	int freeThreadIndex = GetFreeThreadIndex();
	
	if (freeThreadIndex >= 0)
	{
		_threads[freeThreadIndex].StartThread(_tasks->front());
		_tasks->pop();
		_logger->LogTaskAdding((int)_threads[freeThreadIndex].GetThreadHandle());
	}
	else
	{
		_logger->LogThreadPoolIsFilled();
	}


	bool isWarned = false;

	while (!_tasks->empty())
	{
		freeThreadIndex = GetFreeThreadIndex();
		if (freeThreadIndex >= 0)
		{
			_threads[freeThreadIndex].StartThread(_tasks->front());
			_tasks->pop();
			_logger->LogTaskAdding((int)_threads[freeThreadIndex].GetThreadHandle());
			isWarned = false;
		}
		else
		{
			if (freeThreadIndex == -1 && !isWarned)
			{
				_logger->LogThreadPoolIsFilled();
				isWarned = true;
			}
		}
	}

	while (!isFullyCompleted())
	{
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

	_logger->LogThreadPoolFinishedAllTasks();
	return true;
}

ThreadPool::~ThreadPool()
{
	delete _threads; 
}
