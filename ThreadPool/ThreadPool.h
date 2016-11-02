#pragma once

#include "Thread.h";
#include <Windows.h>;
#include <queue>;

class ThreadPool
{
public:
	ThreadPool(int numberOfThreads);
	~ThreadPool();

	void AddNewTask(LPTHREAD_START_ROUTINE threadsRoutine, std::queue<LPTHREAD_START_ROUTINE> *tasks);
	int GetFreeThreadIndex();
	int GetFreeThreadsCount();
	bool ThreadPool::isAvailable(Thread *thread);
	bool ThreadPool::isStillActive(Thread *thread, DWORD status);
	
private:
	Thread *_threads;
	int _numberOfFreeThreads;
	int _numberOfThreads;
};

