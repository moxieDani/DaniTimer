#include "DaniTimer.h"
#include "DaniTImerCore.h"

static DaniTimerCore* timerCore;

DaniTimer::DaniTimer()
{
	timerCore = new DaniTimerCore();
}

DaniTimer::~DaniTimer()
{
	if (timerCore)
		delete timerCore;
}

/* Public Functions */
int DaniTimer::start()
{
    int ret = timerCore->start();
    return ret;
}

int DaniTimer::stop()
{
    int ret = timerCore->stop();
    return ret;
}

int DaniTimer::setStopTimeMilliSec(unsigned long targetStopTimeMilliSec)
{
    int ret = timerCore->setStopTimeMilliSec(targetStopTimeMilliSec);
    return ret;
}

unsigned long DaniTimer::getCurrentTimeSec()
{
	unsigned long ret = timerCore->getCurrentTimeSec();
	return ret;
}

unsigned long DaniTimer::getCurrentTimeMilliSec()
{
	unsigned long ret = timerCore->getCurrentTimeMilliSec();
    return ret;
}

unsigned long DaniTimer::getCurrentTimeMicroSec()
{
	unsigned long ret = timerCore->getCurrentTimeMicroSec();
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
