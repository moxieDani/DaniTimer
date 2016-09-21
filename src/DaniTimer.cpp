#include "DaniTimer.h"

DaniTimer::DaniTimer()
{
    init();
}

DaniTimer::~DaniTimer()
{
    if ( callBackFunc )
        pthread_join(callBackThread, nullptr);
}

/* Private Functions */
int DaniTimer::init()
{
#if defined _WIN32 || _WIN64
    QueryPerformanceFrequency(&frequency);
#endif
    startTimeSec = 0;
    elapsedTimeSec = 0;
    callType = callFrequency::Enum::callTypeFirst;
    intervalMilliSec = 0;
    callBackFunc = nullptr;
    
    return 0;
}

unsigned long DaniTimer::getMeasureTime()
{
    unsigned long ret = 0;
    
#if defined _WIN32 || _WIN64 //windows
    measureTime.QuadPart = 0;
    if ( QueryPerformanceCounter(&measureTime) )
		ret = (unsigned long)(double(measureTime.QuadPart) / (double(frequency.QuadPart)) * 1e6);
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
    
    if ( ret == 0 )
    {
        DaniTimer::callType = callType;
        DaniTimer::intervalMilliSec = intervalMilliSec;
        pthread_create(&callBackThread, NULL, callbackThreadFunc, this);
    }
    
    return ret;
}

void* DaniTimer::callbackThreadFunc(void *data)
{
    DaniTimer* t = (DaniTimer*)data;
    unsigned long currentTime = 0;
    unsigned long newCurrentTime = 0;
    
    while ( t->getElapsedTimeMilliSec() == 0)
    {
        newCurrentTime = t->getCurrentTimeMilliSec();
        
        if ( currentTime/1e3 == newCurrentTime/1e3 )
            continue;
        
        switch (t->callType)
        {
            case callFrequency::Enum::CALL_FUNCTION_EVERYTIME :
                if ( ( newCurrentTime % t->intervalMilliSec ) == 0 )
                    t->callBackFunc(newCurrentTime);
                break;
            case callFrequency::Enum::CALL_FUNCTION_ONCE :
                if ( newCurrentTime == t->intervalMilliSec )
                    t->callBackFunc(newCurrentTime);
            default:
                break;
        }
        
        currentTime = newCurrentTime;
    }
    return nullptr;
}

int DaniTimer::start()
{
    int ret = 1;
    
    if ( startTimeSec == 0 )
    {
        startTimeSec = getMeasureTime();
        ret = 0;
    }
    
    return ret;
}

int DaniTimer::stop()
{
    int ret = 1;
    
    if ( startTimeSec > 0 && elapsedTimeSec == 0 )
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
    
    if ( startTimeSec > 0 && elapsedTimeSec == 0 )
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
