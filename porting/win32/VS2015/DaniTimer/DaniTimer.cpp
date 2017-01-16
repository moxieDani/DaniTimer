#include "DaniTimer.h"
#include "DaniTImerCore.h"
#include "DaniTimerProperty.h"
#include "DaniTimerTypes.h"

static DaniTimerCore* timerCore;

/* Public Functions */
DaniTimer::DaniTimer()
{
	timerCore = new DaniTimerCore();
	timerTask = nullptr;
	onTime = nullptr;
	onTimeRepeatIntervalMilliSec = 100;
}

DaniTimer::~DaniTimer()
{
	if (timerCore)
		delete timerCore;
}

int DaniTimer::start()
{
    int ret = timerCore->start();
	timerTaskStart();
    return ret;
}

int DaniTimer::pause()
{
	int ret = timerCore->pause();
	return ret;
}

int DaniTimer::reset()
{
	int ret = timerCore->reset();
	timerTaskStop();
	return ret;
}

unsigned long long DaniTimer::getElapsedTimeSec()
{
	unsigned long long ret = timerCore->getElapsedTimeSec();
	return ret;
}

unsigned long long DaniTimer::getElapsedTimeMilliSec()
{
	unsigned long long ret = timerCore->getElapsedTimeMilliSec();
    return ret;
}

unsigned long long DaniTimer::getElapsedTimeMicroSec()
{
	unsigned long long ret = timerCore->getElapsedTimeMicroSec();
    return ret;
}

int DaniTimer::setProperty(int propertyType, unsigned long long value)
{
	int ret = TimerType::Error::SUCCESS;
	
	switch (propertyType) {
		case ON_TIME_REAPEAT_INTERVAL_MILLI_SECOND:
			onTimeRepeatIntervalMilliSec = (value > 0) ? value : 10;
			if ( value <= 0 )
				ret = TimerType::Error::SET_PROPERTY_FAILED;
			break;
		default:
			ret = timerCore->setProperty(propertyType, value);
			break;
	}
	return 0;
}

int DaniTimer::setOnTime(onTimeFunction func)
{
	int ret = TimerType::Error::SUCCESS;

	if ( func )
		ret = (onTime = std::move(func)) ? ret : TimerType::Error::SET_ONTIME_EVENT_FAILED;

	return ret;
}

void DaniTimer::timerTaskStart() {
	if ( timerTask == nullptr )
		timerTask = new std::thread (&DaniTimer::onTimeThreadFunc, this);
}

void DaniTimer::timerTaskStop() {
	if (timerTask->joinable())
	{
		timerTask->join();
		delete timerTask;
		timerTask = nullptr;
	}
}

void DaniTimer::onTimeThreadFunc(void *data) {
	DaniTimer* t = (DaniTimer*)data;
	unsigned long long currentTime = 0;
	unsigned long long newCurrentTime = 0;
	
	if ( t )
	{
		while ( t->getCurrentState() != TimerCore::CurrentState::STOP )
		{
			if (t->getCurrentState() == TimerCore::CurrentState::PAUSE ||
				t->getCurrentState() == TimerCore::CurrentState::READY)
				continue;
			
			newCurrentTime = t->getElapsedTimeMilliSec();
			
			if ( currentTime/1e3 == newCurrentTime/1e3 )
				continue;
			
			if ( t->onTime )
			{
				if ( ( newCurrentTime % t->onTimeRepeatIntervalMilliSec ) == 0 )
					t->onTime(newCurrentTime);
			}
			
			currentTime = newCurrentTime;
		}
	}
}

int DaniTimer::getCurrentState() {
	return timerCore->getCurrentState();
}
