#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
#ifdef WIN32
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	stopCount.QuadPart = 0;
#else
#endif
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
#ifdef WIN32
	if (QueryPerformanceCounter(&startCount))
		startTimeMicroSec = double(startCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0);
#else
#endif
	return startTimeMicroSec == 0 ? 1 : 0;
}

int DaniTimer::stop()
{
#ifdef WIN32
	if (QueryPerformanceCounter(&stopCount))
		stopTimeMicroSec = double(stopCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0);
#else
#endif
	return stopTimeMicroSec == 0 ? 1 : 0;
}

double DaniTimer::getCurrentTimeMicroSec()
{
#ifdef WIN32
	LARGE_INTEGER currentCount;
	currentCount.QuadPart = 0;
	QueryPerformanceCounter(&currentCount);
	if (startTimeMicroSec > 0.0)
		currentTimeMicroSec = double(currentCount.QuadPart) / (double(frequency.QuadPart) / 1000000.0) - startTimeMicroSec;
#else
#endif
	return currentTimeMicroSec;
}

double DaniTimer::getElapsedTimeMicroSec()
{
	if (startTimeMicroSec > 0.0 && stopTimeMicroSec > 0.0)
		elapsedTimeMicroSec = stopTimeMicroSec - startTimeMicroSec;
	return elapsedTimeMicroSec;
}