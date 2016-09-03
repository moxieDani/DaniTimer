#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
#if defined _WIN32 || _WIN64
	QueryPerformanceFrequency(&frequency);
#endif
	startTimeSec = 0.0;
	stopTimeSec = 0.0;
	currentTimeSec = 0.0;
	elapsedTimeSec = 0.0;
}

DaniTimer::~DaniTimer()
{
}

unsigned long DaniTimer::getMeasureTime()
{
    unsigned long ret = 0;
    
#if defined _WIN32 || _WIN64 //windows
    measureTime.QuadPart = 0;
    if ( QueryPerformanceCounter(&measureTime) )
        ret = measureTime.QuadPart / frequency.QuadPart) * 1e6;
#elif defined __MACH__ //MacOS
    if ( KERN_SUCCESS == host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &measureClock) )
    {
        if ( KERN_SUCCESS == clock_get_time(measureClock, &measureTime) )
            ret = ( ( measureTime.tv_sec * 1e9 ) + measureTime.tv_nsec ) / 1e3;
        mach_port_deallocate(mach_task_self(), measureClock);
    }
#else //Linux
    if( 0 == clock_gettime(CLOCK_MONOTONIC, &measureTime) )
        ret = ( ( measureTime.tv_sec * 1e9 ) + measureTime.tv_nsec ) / 1e3;
#endif
    return ret;
}

int DaniTimer::start()
{
    startTimeSec = DaniTimer::getMeasureTime();
    return startTimeSec == 0 ? 1 : 0;
}

int DaniTimer::stop()
{
    stopTimeSec = DaniTimer::getMeasureTime();
	return stopTimeSec == 0 ? 1 : 0;
}

unsigned long DaniTimer::getCurrentTimeSec()
{
	return DaniTimer::getCurrentTimeMilliSec() / 1e3;
}

unsigned long DaniTimer::getCurrentTimeMilliSec()
{
    return DaniTimer::getCurrentTimeMicroSec() / 1e3;
}

unsigned long DaniTimer::getCurrentTimeMicroSec()
{
    if ( startTimeSec > 0.0 )
        currentTimeSec = DaniTimer::getMeasureTime() - startTimeSec;
    return currentTimeSec;
}

unsigned long DaniTimer::getElapsedTimeSec()
{
	return DaniTimer::getElapsedTimeMilliSec() / 1e3;
}

unsigned long DaniTimer::getElapsedTimeMilliSec()
{
    return DaniTimer::getElapsedTimeMicroSec() / 1e3;
}

unsigned long DaniTimer::getElapsedTimeMicroSec()
{
    if (startTimeSec > 0.0 && stopTimeSec > 0.0)
        elapsedTimeSec = stopTimeSec - startTimeSec;
    return elapsedTimeSec;
}
