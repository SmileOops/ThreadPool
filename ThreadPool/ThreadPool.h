#pragma once

#include "Thread.h";
#include "Logger.h"
#include <Windows.h>;
#include <queue>;

class ThreadPool
{
public:
	ThreadPool(int numberOfThreads);
	~ThreadPool();

	void AddNewTask(LPTHREAD_START_ROUTINE threadRoutine);
	void StartExecutingTasks();
	int GetFreeThreadIndex();
	bool isAvailable(Thread *thread);
	bool isStillActive(Thread *thread, DWORD status);
	bool isFullyCompleted();

private:
	Thread *_threads;
	std::queue<LPTHREAD_START_ROUTINE> *_tasks;
	Logger *_logger;
	int _numberOfFreeThreads;
	int _numberOfThreads;
};

