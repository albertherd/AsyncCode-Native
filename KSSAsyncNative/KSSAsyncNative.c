// KSSAsyncNative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "threads.h"
#include "threadpools.h"


int main()
{
	BenchmarkThreads(FALSE);
	BenchmarkThreads(TRUE);
	BenchmarkThreadPools();
    return 0;
}

