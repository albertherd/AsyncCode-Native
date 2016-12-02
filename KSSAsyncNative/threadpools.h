#pragma once

void BenchmarkThreadPools();
VOID CALLBACK ThreadPoolTimerFunc(PVOID lpParam, BOOLEAN timerOrWaitFired);
VOID CALLBACK ThreadPoolBenchmarker(PTP_CALLBACK_INSTANCE instance, PVOID context, PTP_WORK work);