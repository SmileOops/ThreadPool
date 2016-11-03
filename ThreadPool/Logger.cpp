#include "Logger.h"

Logger::Logger(char *logPath)
{
	_logFile.open(logPath);
}

void Logger::LogThreadPoolInitialization(int numberOfThreads)
{
	_logFile << "Thread pool was initialized with " << numberOfThreads << " threads.\n";
}

void Logger::LogTaskAdding(int hThread)
{
	_logFile << "Task was started in thread " << hThread << ".\n";
}

void Logger::LogThreadPoolIsFilled()
{
	_logFile << "Cannot add a task. Thread pool is filled with busy threads. Waiting for free one.\n";
}

Logger::~Logger()
{
	_logFile.close();
}
