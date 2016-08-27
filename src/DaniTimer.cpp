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

long double DaniTimer::getMeasureTime()
{
    long double ret = 0;
    
#if defined _WIN32 || _WIN64
    measureTime.QuadPart = 0;
    if ( QueryPerformanceCounter(&measureTime) )
        ret = double(measureTime.QuadPart) / (double(frequency.QuadPart));
#elif defined __MACH__
    if ( KERN_SUCCESS == host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &measureClock) )
    {
        if ( KERN_SUCCESS == clock_get_time(measureClock, &measureTime) )
            ret = measureTime.tv_sec + double(measureTime.tv_nsec / 1e9);
        mach_port_deallocate(mach_task_self(), measureClock);
    }
#else
    if( 0 == clock_gettime(CLOCK_MONOTONIC, &measureTime) )
        ret = measureTime.tv_sec + double(measureTime.tv_nsec / 1e9);
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

long double DaniTimer::getCurrentTimeSec()
{
    if ( startTimeSec > 0.0 )
        currentTimeSec = DaniTimer::getMeasureTime() - startTimeSec;
	return currentTimeSec;
}

long double DaniTimer::getCurrentTimeMilliSec()
{
    return DaniTimer::getCurrentTimeSec() * 1000.0;
}

long double DaniTimer::getCurrentTimeMicroSec()
{
    return DaniTimer::getCurrentTimeMilliSec() * 1000.0;
}

long double DaniTimer::getElapsedTimeSec()
{
	if (startTimeSec > 0.0 && stopTimeSec > 0.0)
		elapsedTimeSec = stopTimeSec - startTimeSec;
	return elapsedTimeSec;
}

long double DaniTimer::getElapsedTimeMilliSec()
{
    return DaniTimer::getElapsedTimeSec() * 1000.0;
}

long double DaniTimer::getElapsedTimeMicroSec()
{
    return DaniTimer::getElapsedTimeMilliSec() * 1000.0;
}
