#include "stdafx.h"
#include "threadpools.h"
#include "intensiveworker.h"

long workedThreads;

void BenchmarkThreadPools()
{
	PTP_POOL threadPool = CreateThreadpool(NULL);
	TP_CALLBACK_ENVIRON callbackEnviornment;
	InitializeThreadpoolEnvironment(&callbackEnviornment);
	SetThreadpoolCallbackPool(&callbackEnviornment, threadPool);
	PTP_CLEANUP_GROUP cleanupGroup = CreateThreadpoolCleanupGroup();
	PTP_WORK threadWork = CreateThreadpoolWork(ThreadPoolBenchmarker, NULL, &callbackEnviornment);
	HANDLE hTimerQueue = CreateTimerQueue();
	HANDLE hTimer = NULL;
	CreateTimerQueueTimer(&hTimer, hTimerQueue, ThreadPoolTimerFunc, NULL, 1000, 1000, 0);


	while (1) {
		SubmitThreadpoolWork(threadWork);
		InterlockedIncrement(&workedThreads);
	}

	CloseThreadpoolWork(threadWork);
	CloseThreadpoolCleanupGroup(cleanupGroup);
	DestroyThreadpoolEnvironment(&callbackEnviornment);
	CloseThreadpool(threadPool);
}


VOID CALLBACK ThreadPoolTimerFunc(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
	UNREFERENCED_PARAMETER(timerOrWaitFired);
	_tprintf(_TEXT("Threads worked on per sec - %d\n"), workedThreads);
	InterlockedExchange(&workedThreads, 0);
}

VOID CALLBACK ThreadPoolBenchmarker(PTP_CALLBACK_INSTANCE instance, PVOID context, PTP_WORK work)
{
	InterlockedIncrement(&workedThreads);
	DoIntensiveWork();
}