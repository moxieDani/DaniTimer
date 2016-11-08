#include "DaniTimerCore.h"

#if defined _WIN32 || _WIN64
    #define TALBODY_CLASS TALBodyWindows
#elif defined __APPLE__
    #define TALBODY_CLASS TALBodyMacOSX
#else
    #define TALBODY_CLASS TALBodyLinux
#endif

#define STRINGIZE(x) #x                      // TALBodyXXXX -> "TALBodyXXXX"
#define GET_TALBODY_HEADER(x) STRINGIZE(x.h) // "TALBodyXXXX"   -> "TALBodyXXXX.h"

#include GET_TALBODY_HEADER(TALBODY_CLASS)   // #include "TALBodyXXXX.h"

DaniTimerCore::DaniTimerCore()
{
    tal = new TALBODY_CLASS;
    init();
}

DaniTimerCore::~DaniTimerCore()
{
    if ( callBackFunc )
        callBackFunc = nullptr;
    
    if ( callBackThread )
    {
        callBackThread->join();
        delete callBackThread;
    }
    if ( tal )
        delete tal;
}

/* Private Functions */
int DaniTimerCore::init()
{
    startTimeSec = 0;
    elapsedTimeSec = 0;
    callType = callFrequency::Enum::NONE;
    userSetTimeMilliSec = 0;
    callBackFunc = nullptr;
    return tal->init();
}

unsigned long DaniTimerCore::getMeasureTime()
{
    return tal->getMeasureTime();
}

/* Public Functions */
int DaniTimerCore::registerCallback(DaniTimerCoreCallbackFunc callback, callFrequency::Enum callType, unsigned long userSetTimeMilliSec)
{
    int ret = 1;
    
    if ( callback )
        ret = ( callBackFunc = std::move(callback) ) ? 0 : 1;
    
    if ( ret == 0 )
    {
        DaniTimerCore::callType = callType;
        DaniTimerCore::userSetTimeMilliSec = userSetTimeMilliSec;
    }
    
    return ret;
}

void DaniTimerCore::callbackThreadFunc(void *data)
{
    DaniTimerCore* t = (DaniTimerCore*)data;
    unsigned long currentTime = 0;
    unsigned long newCurrentTime = 0;
    
    while ( t->getElapsedTimeMilliSec() == 0 ||
           currentTime <= t->targetStopTimeMilliSec )
    {
        newCurrentTime = t->getCurrentTimeMilliSec();
        
        if ( currentTime/1e3 == newCurrentTime/1e3 )
            continue;
        
        if ( t->callBackFunc )
        {
            switch (t->callType)
            {
                case callFrequency::Enum::CALL_EVERYTIME :
                    if ( ( newCurrentTime % t->userSetTimeMilliSec ) == 0 )
                        t->callBackFunc(newCurrentTime);
                    break;
                case callFrequency::Enum::CALL_ONCE :
                    if ( newCurrentTime == t->userSetTimeMilliSec )
                        t->callBackFunc(newCurrentTime);
                default:
                    break;
            }
        }
        currentTime = newCurrentTime;
    }
}

int DaniTimerCore::start()
{
    int ret = 1;
    
    if ( startTimeSec == 0 )
    {
        callBackThread = new std::thread (&DaniTimerCore::callbackThreadFunc, this);
        startTimeSec = getMeasureTime();
        elapsedTimeSec = 0;
        ret = 0;
    }
    
    return ret;
}

int DaniTimerCore::stop()
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

int DaniTimerCore::setStopTimeMilliSec(unsigned long targetStopTimeMilliSec)
{
    int ret = 1;
    
    if ( elapsedTimeSec == 0 )
    {
        DaniTimerCore::targetStopTimeMilliSec = targetStopTimeMilliSec;
        ret = 0;
    }
    
    return ret;
}

unsigned long DaniTimerCore::getCurrentTimeSec()
{
	return (unsigned long)(getCurrentTimeMilliSec() / 1e3);
}

unsigned long DaniTimerCore::getCurrentTimeMilliSec()
{
    return (unsigned long)(getCurrentTimeMicroSec() / 1e3);
}

unsigned long DaniTimerCore::getCurrentTimeMicroSec()
{
    unsigned long ret = 0;
    
    if ( startTimeSec > 0 && elapsedTimeSec == 0 )
        ret = getMeasureTime() - startTimeSec;
    
    return (unsigned long)ret;
}

unsigned long DaniTimerCore::getElapsedTimeSec()
{
	return (unsigned long)(getElapsedTimeMilliSec() / 1e3);
}

unsigned long DaniTimerCore::getElapsedTimeMilliSec()
{
    return (unsigned long)(getElapsedTimeMicroSec() / 1e3);
}

unsigned long DaniTimerCore::getElapsedTimeMicroSec()
{
    return elapsedTimeSec;
}
