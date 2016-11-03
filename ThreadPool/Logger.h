#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
class Logger
{
public:
	Logger(char *logPath);
	~Logger();

	void LogThreadPoolInitialization(int numberOfThreads);
	void LogTaskAdding(int threadIndex);
	void LogThreadPoolIsFilled();
	void LogThreadPoolFinishedAllTasks();
	
private:
	std::ofstream _logFile;
};

