#include "DaniTimer.h"
#include "DaniTImerCore.h"

static DaniTimerCore* timerCore;

/* Public Functions */
DaniTimer::DaniTimer()
{
	timerCore = new DaniTimerCore();
}

DaniTimer::~DaniTimer()
{
	if (timerCore)
		delete timerCore;
}

int DaniTimer::setTimerMode(int timerMode)
{
	int ret = timerCore->setTimerMode(timerMode);
	return ret;
}

int DaniTimer::setStopTimeMilliSec(unsigned long targetStopTimeMilliSec)
{
	int ret = timerCore->setStopTimeMilliSec(targetStopTimeMilliSec);
	return ret;
}

int DaniTimer::setStartTimeMilliSec(unsigned long targetTimeMilliSec)
{
	int ret = timerCore->setStartTimeMilliSec(targetTimeMilliSec);
	return ret;
}

int DaniTimer::start()
{
    int ret = timerCore->start();
    return ret;
}

int DaniTimer::pause()
{
	int ret = timerCore->pause();
	return ret;
}

int DaniTimer::resume()
{
	int ret = timerCore->resume();
	return ret;
}

int DaniTimer::stop()
{
    int ret = timerCore->stop();
    return ret;
}

int DaniTimer::reset()
{
	int ret = timerCore->reset();
	return ret;
}

unsigned long DaniTimer::getElapsedTimeSec()
{
	unsigned long ret = timerCore->getElapsedTimeSec();
	return ret;
}

unsigned long DaniTimer::getElapsedTimeMilliSec()
{
	unsigned long ret = timerCore->getElapsedTimeMilliSec();
    return ret;
}

unsigned long DaniTimer::getElapsedTimeMicroSec()
{
	unsigned long ret = timerCore->getElapsedTimeMicroSec();
    return ret;
}
