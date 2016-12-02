#pragma once

void BenchmarkThreads(BOOL withSemaphore);
VOID CALLBACK ThreadTimerFunc(PVOID lpParam, BOOLEAN timerOrWaitFired);
DWORD WINAPI ThreadBenchmarkFunc(LPVOID parameter);
DWORD WINAPI ThreadBenchmarker(LPVOID parameter);