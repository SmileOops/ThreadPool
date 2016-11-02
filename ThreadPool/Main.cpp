#include "ThreadPool.h"

void taskTwo()
{
	Sleep(2000);

	printf("Task two completed\n");
}

void taskThree()
{
	Sleep(3000);

	printf("Task three completed\n");
}

void taskOne()
{
	Sleep(1000);
	taskTwo();
	Sleep(1000);

	printf("Task one completed\n");
}


int main()
{
	ThreadPool *tp = new ThreadPool(3);
	std::queue<LPTHREAD_START_ROUTINE> *tasks = new std::queue<LPTHREAD_START_ROUTINE>;
	
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskOne, tasks);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskOne, tasks);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree, tasks);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree, tasks);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree, tasks);
	
	while (!tasks->empty())
	{
		if (tp->GetFreeThreadIndex() >= 0)
		{
			tp->AddNewTask(tasks->front(), tasks);
			tasks->pop();
		}
	}

	Sleep(10000);

	return 0;
}
