#include "stdafx.h"
#include "threads.h"
#include "intensiveworker.h"

long createdThreads = 0;

void BenchmarkThreads(BOOL withSemaphore)
{
	HANDLE hBenchmarkInterval = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hTimerQueue = CreateTimerQueue();
	HANDLE hTimer = NULL;
	CreateTimerQueueTimer(&hTimer, hTimerQueue, ThreadTimerFunc, NULL, 1000, 1000, 0);
	_tprintf(_TEXT("Started benchmarking threads\n"));

	if (withSemaphore) {
		HANDLE hSem = CreateSemaphore(NULL, 4, 4, NULL);
		while (1) {
			WaitForSingleObject(hSem, INFINITE);
			HANDLE hThread = CreateThread(NULL, 0, ThreadBenchmarker, &hSem, 0, NULL);
			CloseHandle(hThread);
		}
	}
	else {
		while (1) {
			HANDLE hThread = CreateThread(NULL, 0, ThreadBenchmarker, NULL, 0, NULL);
			CloseHandle(hThread);
		}
	}

	DeleteTimerQueueTimer(hTimerQueue, hTimer, INVALID_HANDLE_VALUE);
	DeleteTimerQueue(hTimerQueue);
	CloseHandle(hBenchmarkInterval);
}

VOID CALLBACK ThreadTimerFunc(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
	UNREFERENCED_PARAMETER(timerOrWaitFired);
	_tprintf(_TEXT("Threads created per sec - %d\n"), createdThreads);
	InterlockedExchange(&createdThreads, 0);
}

DWORD WINAPI ThreadBenchmarker(LPVOID parameter)
{
	InterlockedAdd(&createdThreads, 1);
	DoIntensiveWork();
	PHANDLE phSem = (PHANDLE)parameter;
	if (phSem) {
		ReleaseSemaphore(*phSem, 1, NULL);
	}
	ExitThread(0);
	return 0;
}