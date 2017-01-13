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
	measuredStartPoint              = 0;
	measuredPausePoint              = 0;
	targetEndTimeMilliSec         = 0;
	targetBeginTimeMilliSec        = 0;
	callbackRepeatIntervalMilliSec = 10;
	
	//Preference
    timerCountMode = TimerCore::CountMode::COUNTUP;
	timerStatus    = TimerCore::CurrentState::STOP;
	
	//Timer Adaptation Layer
	tal = new TALBODY_CLASS;
	
    //Timer Task
    timerTask = nullptr;

	return ret;
}

unsigned long long DaniTimerCore::getMeasureTime()
{
	unsigned long long ret = tal->getMeasureTime();
	return ret;
}

void DaniTimerCore::callbackThreadFunc(void *data)
{
	DaniTimerCore* t = (DaniTimerCore*)data;
	unsigned long long currentTime = 0;
	unsigned long long newCurrentTime = 0;
	
	if ( t )
	{
        while ( t->timerStatus != TimerCore::CurrentState::STOP )
		{
			if (t->timerStatus == TimerCore::CurrentState::PAUSE ||
                t->timerStatus == TimerCore::CurrentState::READY)
				continue;
			
			newCurrentTime = t->getElapsedTimeMilliSec();
			
			if ( currentTime/1e3 == newCurrentTime/1e3 )
				continue;
			
			/*
            if ( t->registeredCallBackFunc )
            {
                if ( ( newCurrentTime % t->callbackRepeatIntervalMilliSec ) == 0 )
                    t->registeredCallBackFunc(newCurrentTime);
            }
            */
			
			if ( (t->timerCountMode == TimerCore::CountMode::COUNTUP && newCurrentTime > t->targetEndTimeMilliSec) ||
                (t->timerCountMode == TimerCore::CountMode::COUNTDOWN && newCurrentTime < t->targetEndTimeMilliSec) )
                t->reset();
            
			currentTime = newCurrentTime;
		}
	}
}

void DaniTimerCore::timerTaskStart()
{
    if ( timerTask == nullptr )
    {
        timerTask = new std::thread (&DaniTimerCore::callbackThreadFunc, this);
        timerStatus = TimerCore::CurrentState::READY;
    }
}

void DaniTimerCore::timerTaskStop()
{
    if ( timerTask )
    {
        timerTask->join();
        delete timerTask;
        timerTask = nullptr;
        timerStatus = TimerCore::CurrentState::STOP;
    }
}

/* Public Functions */
DaniTimerCore::DaniTimerCore()
{
	init();
    //timerTaskStart();
}

DaniTimerCore::~DaniTimerCore()
{
	reset();
    //timerTaskStop();
	
	if ( tal )
		delete tal;
}

int DaniTimerCore::setTimerMode(int timerMode)
{
    int ret = TimerCore::Error::INVALID_STATE;
	
	if ( timerStatus == TimerCore::CurrentState::READY )
	{
		timerCountMode = timerMode;
        ret = TimerCore::Error::SUCCESS;
	}
	
	return ret;
}

int DaniTimerCore::setBeginTimeMilliSec(unsigned long long targetTimeMilliSec)
{
    int ret = TimerCore::Error::INVALID_STATE;
    
    if ( timerStatus == TimerCore::CurrentState::READY )
    {
        targetBeginTimeMilliSec = targetTimeMilliSec;
        ret = TimerCore::Error::SUCCESS;
    }
    
    return ret;
}

int DaniTimerCore::setEndTimeMilliSec(unsigned long long targetTimeMilliSec)
{
    int ret = TimerCore::Error::INVALID_STATE;
	
	if ( timerStatus == TimerCore::CurrentState::READY )
	{
		targetEndTimeMilliSec = targetTimeMilliSec;
        ret = TimerCore::Error::SUCCESS;
	}
	
	return ret;
}

int DaniTimerCore::start()
{
    int ret = TimerCore::Error::SUCCESS;
    
    if ( timerCountMode == TimerCore::CountMode::COUNTDOWN )
    {
        if ( targetEndTimeMilliSec >= targetBeginTimeMilliSec || targetBeginTimeMilliSec == 0)
        {
            reset();
            ret = TimerCore::Error::START_FAILED;
        }
    }
    else
    {
        if ( targetEndTimeMilliSec < targetBeginTimeMilliSec)
        {
            reset();
            ret = TimerCore::Error::START_FAILED;
        }
    }
    
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
    
    return ret;
}

int DaniTimerCore::pause()
{
    int ret = TimerCore::Error::INVALID_STATE;
	
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
	callbackRepeatIntervalMilliSec = 10;
    
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
	
	if ( timerCountMode == TimerCore::CountMode::COUNTDOWN )
		ret = (targetBeginTimeMilliSec * 1e3) - ret;
    else
        ret = (targetBeginTimeMilliSec * 1e3) + ret;
    
	return ret > 0 ? ret : 0;
}

int DaniTimerCore::getCurrentState()
{
	return timerStatus;
}

template <typename PropertyValue>
int  DaniTimerCore::setProperty(int propertyType, PropertyValue value)
{
	int ret = TimerCore::Error::SUCCESS;
	
	switch (propertyType) {
		case TimerCore::Property::TIMER_MODE:
			timerCountMode = value;
			break;
		case TimerCore::Property::BEGIN_TIME_MILLI_SECOND:
			targetBeginTimeMilliSec = value;
			break;
		case TimerCore::Property::END_TIME_MILLI_SECOND:
			targetEndTimeMilliSec = value;
			break;
		default:
			ret = TimerCore::Error::SET_PROPERTY_FAILED;
			break;
	}
	
	return ret;
}
