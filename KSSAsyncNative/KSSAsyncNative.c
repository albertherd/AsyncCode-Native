// KSSAsyncNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "threads.h"
#include "threadpools.h"


int main(int argc, char** argv)
{
	if (argc < 2) {
		_tprintf(_TEXT("1) Benchmark Threads no Semaphore\r\n2) Benchmark Threads with Semaphore\r\n3) Benchmark ThreadPools"));
		return 0;
	}

	int function = atoi(argv[1]);

	switch (function) {
	case 1:
		BenchmarkThreads(FALSE);
		break;
	case 2:
		BenchmarkThreads(TRUE);
		break;
	case 3: BenchmarkThreadPools();
		break;
	}


    return 0;
}

