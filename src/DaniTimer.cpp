#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
    init();
}

DaniTimer::~DaniTimer()
{
}

/* Private Functions */
int DaniTimer::init()
{
#if defined _WIN32 || _WIN64
    QueryPerformanceFrequency(&frequency);
#endif
    startTimeSec = 0;
    elapsedTimeSec = 0;
    callBackFunc = nullptr;
    pthread_create(&callBackThread, NULL, callbackThreadFunc, NULL);
    
    return 0;
}

unsigned long DaniTimer::getMeasureTime()
{
    unsigned long ret = 0;
    
#if defined _WIN32 || _WIN64 //windows
    measureTime.QuadPart = 0;
    if ( QueryPerformanceCounter(&measureTime) )
		ret = (unsigned long)(double(measureTime.QuadPart) / (double(frequency.QuadPart)) * 1e6);

        //ret = (unsigned long)((measureTime.QuadPart / frequency.QuadPart) * 1e6);
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

/* Public Functions */
int DaniTimer::registerCallback(DaniTimerCallbackFunc callback, callFrequency::Enum callType, unsigned long intervalMilliSec)
{
    int ret = 1;
    
    if ( callback )
        ret = ( callBackFunc = std::move(callback) ) ? 0 : 1;
    
    if ( ret == 0)
    {
        DaniTimer::callType = callType;
        DaniTimer::intervalMilliSec = intervalMilliSec;
    }
    
    return ret;
}

void* DaniTimer::callbackThreadFunc(void *data)
{
    while ( getElapsedTimeMilliSec() == 0)
    {
        switch (callType) {
            case callFrequency::Enum::CALL_FUNCTION_EVERYTIME :
                if ( (getCurrentTimeMicroSec() % intervalMilliSec) == 0 )
                    callBackFunc(10);
                break;
            case callFrequency::Enum::CALL_FUNCTION_ONCE :
                if ( getCurrentTimeMicroSec() == intervalMilliSec )
                    callBackFunc(10);
            default:
                break;
        }
    }
    return nullptr;
}

int DaniTimer::start()
{
    int ret = 1;
    if (startTimeSec == 0)
    {
        startTimeSec = getMeasureTime();
        ret = 0;
    }
    
    if ( callBackFunc )
    {
        //Do the callback function. -> Maybe it will execute in a thread later.
        int status;
        pthread_join(callBackThread, (void **)&status);
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
	return (unsigned long)(getCurrentTimeMilliSec() / 1e3);
}

unsigned long DaniTimer::getCurrentTimeMilliSec()
{
    return (unsigned long)(getCurrentTimeMicroSec() / 1e3);
}

unsigned long DaniTimer::getCurrentTimeMicroSec()
{
    unsigned long ret = 0;
    if ( startTimeSec > 0 && elapsedTimeSec == 0)
        ret = getMeasureTime() - startTimeSec;
    
    return (unsigned long)ret;
}

unsigned long DaniTimer::getElapsedTimeSec()
{
	return (unsigned long)(getElapsedTimeMilliSec() / 1e3);
}

unsigned long DaniTimer::getElapsedTimeMilliSec()
{
    return (unsigned long)(getElapsedTimeMicroSec() / 1e3);
}

unsigned long DaniTimer::getElapsedTimeMicroSec()
{
    return elapsedTimeSec;
}
