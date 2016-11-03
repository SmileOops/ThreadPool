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
	
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskOne);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskOne);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree);
	tp->AddNewTask((LPTHREAD_START_ROUTINE)taskThree);
	
	tp->StartExecutingTasks();

	return 0;
}
