#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	stopCount.QuadPart = 0;
	startTimeMicroSec = 0;
	stopTimeMicroSec = 0;
	currentTimeMicroSec = 0;
	elapsedTimeMicroSec = 0;
}

DaniTimer::~DaniTimer()
{
}

int DaniTimer::start()
{
	if (QueryPerformanceCounter(&startCount))
		startTimeMicroSec = double(startCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0);
	return startTimeMicroSec == 0 ? 1 : 0;
}

int DaniTimer::stop()
{
	if (QueryPerformanceCounter(&stopCount))
		stopTimeMicroSec = double(stopCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0);
	return stopTimeMicroSec == 0 ? 1 : 0;
}

double DaniTimer::getCurrentTimeMicroSec()
{
	LARGE_INTEGER currentCount;
	currentCount.QuadPart = 0;
	QueryPerformanceCounter(&currentCount);
	if (startTimeMicroSec > 0.0)
		currentTimeMicroSec = double(currentCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0) - startTimeMicroSec;
	return currentTimeMicroSec;
}

double DaniTimer::getElapsedTimeMicroSec()
{
	if (startTimeMicroSec > 0.0 && stopTimeMicroSec > 0.0)
		elapsedTimeMicroSec = stopTimeMicroSec - startTimeMicroSec;
	return elapsedTimeMicroSec;
}