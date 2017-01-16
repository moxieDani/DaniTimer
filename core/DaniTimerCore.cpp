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

/* Private Functions */
int DaniTimerCore::init()
{
    int ret = TimerCore::Error::INIT_FAILED;
	
	//Times for calculation
	measuredStartPoint             = 0;
	measuredPausePoint             = 0;
	targetEndTimeMilliSec          = 0;
	targetBeginTimeMilliSec        = 0;
	
	//Preference
    timerCountMode = TimerCore::CountMode::COUNTUP;
	timerStatus    = TimerCore::CurrentState::STOP;
	
	//Timer Adaptation Layer
	tal = new TALBODY_CLASS();

	return ret;
}

unsigned long long DaniTimerCore::getMeasureTime()
{
	unsigned long long ret = tal->getMeasureTime();
    
	return ret;
}

/* Public Functions */
DaniTimerCore::DaniTimerCore()
{
	init();
}

DaniTimerCore::~DaniTimerCore()
{
	if ( tal )
		delete tal;
    reset();
}

int DaniTimerCore::start()
{
    int ret = TimerCore::Error::SUCCESS;
    
    if ( (timerCountMode == TimerCore::CountMode::COUNTDOWN && (targetBeginTimeMilliSec == 0 || targetEndTimeMilliSec >= targetBeginTimeMilliSec)) ||
        ( timerCountMode == TimerCore::CountMode::COUNTUP   && (targetEndTimeMilliSec > 0    && targetEndTimeMilliSec < targetBeginTimeMilliSec)) )
    {
        reset();
        ret = TimerCore::Error::START_FAILED;
    }
    
    if ( ret == TimerCore::Error::SUCCESS)
    {
        if ( timerStatus == TimerCore::CurrentState::STOP ||
            timerStatus == TimerCore::CurrentState::READY)
        {
            measuredStartPoint = getMeasureTime();
            timerStatus = TimerCore::CurrentState::PROGRESS;
        }
        else if (timerStatus == TimerCore::CurrentState::PAUSE)
        {
            measuredStartPoint += (getMeasureTime() - measuredPausePoint);
            timerStatus = TimerCore::CurrentState::PROGRESS;
        }
        else
        {
            ret = TimerCore::Error::INVALID_STATE;
        }
    }
    
    return ret;
}

int DaniTimerCore::pause()
{
    int ret = TimerCore::Error::PAUSE_FAILED;
	
    if ( timerStatus == TimerCore::CurrentState::PROGRESS )
    {
		measuredPausePoint = getMeasureTime();
        timerStatus = TimerCore::CurrentState::PAUSE;
        ret = TimerCore::Error::SUCCESS;
    }
    
	return ret;
}

int DaniTimerCore::reset()
{
    int ret = TimerCore::Error::SUCCESS;

	//Times for calculation
	measuredStartPoint              = 0;
	measuredPausePoint              = 0;
	targetEndTimeMilliSec         = 0;
	targetBeginTimeMilliSec        = 0;
    
	//Preference
	timerStatus = TimerCore::CurrentState::STOP;

	return ret;
}

unsigned long long DaniTimerCore::getElapsedTimeSec()
{
	unsigned long long ret = (unsigned long long)(getElapsedTimeMilliSec() / 1e3);
	
	return ret;
}

unsigned long long DaniTimerCore::getElapsedTimeMilliSec()
{
	unsigned long long ret = (unsigned long long)(getElapsedTimeMicroSec() / 1e3);
	
    return ret;
}

unsigned long long DaniTimerCore::getElapsedTimeMicroSec()
{
	unsigned long long ret = 0;
	unsigned long long measuredTime = getMeasureTime();
    
	if ( timerStatus == TimerCore::CurrentState::PROGRESS )
		ret = measuredTime - measuredStartPoint;
	else if (timerStatus == TimerCore::CurrentState::PAUSE)
		ret = (measuredTime - measuredStartPoint) - (measuredTime - measuredPausePoint);
	
	if ( timerCountMode == TimerCore::CountMode::COUNTUP )
    {
        ret = (targetBeginTimeMilliSec * 1e3) + ret;
        if ( (targetEndTimeMilliSec * 1e3) > 0 && ret > (targetEndTimeMilliSec * 1e3) )
        {
            ret = targetEndTimeMilliSec * 1e3;
            reset();
        }
    }
    else
    {
        ret = (targetBeginTimeMilliSec * 1e3) - ret;
        if (ret < targetEndTimeMilliSec * 1e3)
        {
            ret = targetEndTimeMilliSec * 1e3;
            reset();
        }
    }
    
	return ret > 0 ? ret : 0;
}

int DaniTimerCore::getCurrentState()
{
	return timerStatus;
}

int DaniTimerCore::setProperty(int type, unsigned long long value)
{
	int ret = TimerCore::Error::SUCCESS;
	
    if ( timerStatus == TimerCore::CurrentState::STOP )
    {
        switch (type) {
            case TimerCore::Property::TIMER_MODE:
                timerCountMode = (int)value;
                break;
            case TimerCore::Property::BEGIN_TIME_MILLI_SECOND:
                targetBeginTimeMilliSec = (unsigned long long)value;
                break;
            case TimerCore::Property::END_TIME_MILLI_SECOND:
                targetEndTimeMilliSec = (unsigned long long)value;
                break;
            default:
                ret = TimerCore::Error::SET_PROPERTY_FAILED;
                break;
        }
    }
    else
        ret = TimerCore::Error::INVALID_STATE;
    
	return ret;
}
