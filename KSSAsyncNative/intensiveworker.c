#include "intensiveworker.h"

void DoIntensiveWork()
{
	for (volatile unsigned short i = 0; i < 32; i++) {}
}
