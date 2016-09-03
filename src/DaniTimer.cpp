#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
    init();
}

DaniTimer::~DaniTimer()
{
}

int DaniTimer::init()
{
#if defined _WIN32 || _WIN64
    QueryPerformanceFrequency(&frequency);
#endif
    startTimeSec = 0;
    elapsedTimeSec = 0;
    return 0;
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
    int ret = 1;
    if (startTimeSec == 0)
    {
        startTimeSec = getMeasureTime();
        ret = 0;
    }
    return ret;
}

int DaniTimer::stop()
{
    int ret = 1;
    if ( startTimeSec > 0 && elapsedTimeSec == 0)
    {
        elapsedTimeSec = getMeasureTime() - startTimeSec;
        startTimeSec = 0;
        ret = 0;
    }
	return ret;
}

unsigned long DaniTimer::getCurrentTimeSec()
{
	return getCurrentTimeMilliSec() / 1e3;
}

unsigned long DaniTimer::getCurrentTimeMilliSec()
{
    return getCurrentTimeMicroSec() / 1e3;
}

unsigned long DaniTimer::getCurrentTimeMicroSec()
{
    unsigned long ret = 0;
    if ( startTimeSec > 0 && elapsedTimeSec == 0)
        ret = getMeasureTime() - startTimeSec;
    return ret;
}

unsigned long DaniTimer::getElapsedTimeSec()
{
	return getElapsedTimeMilliSec() / 1e3;
}

unsigned long DaniTimer::getElapsedTimeMilliSec()
{
    return getElapsedTimeMicroSec() / 1e3;
}

unsigned long DaniTimer::getElapsedTimeMicroSec()
{
    return elapsedTimeSec;
}
