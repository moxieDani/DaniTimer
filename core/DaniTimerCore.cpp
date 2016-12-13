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
	startTimeMicroSec              = 0;
	pauseTimeMicroSec              = 0;
	targetStopTimeMilliSec         = 0;
	targetStartTimeMilliSec        = 0;
	callbackRepeatIntervalMilliSec = 10;
	
	//Callback
	registeredCallBackFunc = nullptr;
	
	//Preference
    timerCountMode = TimerCore::CountMode::COUNTUP;
	timerStatus    = TimerCore::CurrentState::STOP;
	
	//Timer Adaptation Layer
	tal = new TALBODY_CLASS;
	ret = tal->init();
    
    //Timer Task
    timerTask = nullptr;

	return ret;
}

unsigned long DaniTimerCore::getMeasureTime()
{
	unsigned long ret = tal->getMeasureTime();
	return ret;
}

void DaniTimerCore::callbackThreadFunc(void *data)
{
	DaniTimerCore* t = (DaniTimerCore*)data;
	unsigned long currentTime = 0;
	unsigned long newCurrentTime = 0;
	
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
			
            if ( t->registeredCallBackFunc )
            {
                if ( ( newCurrentTime % t->callbackRepeatIntervalMilliSec ) == 0 )
                    t->registeredCallBackFunc(newCurrentTime);
            }
            
			if ( (t->timerCountMode == TimerCore::CountMode::COUNTUP && newCurrentTime > t->targetStopTimeMilliSec) ||
                (t->timerCountMode == TimerCore::CountMode::COUNTDOWN && newCurrentTime < t->targetStopTimeMilliSec) )
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
    timerTaskStart();
}

DaniTimerCore::~DaniTimerCore()
{
	reset();
    timerTaskStop();
    
    if ( registeredCallBackFunc )
		registeredCallBackFunc = nullptr;
	
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

int DaniTimerCore::setStartTimeMilliSec(unsigned long targetTimeMilliSec)
{
    int ret = TimerCore::Error::INVALID_STATE;
    
    if ( timerStatus == TimerCore::CurrentState::READY )
    {
        targetStartTimeMilliSec = targetTimeMilliSec;
        ret = TimerCore::Error::SUCCESS;
    }
    
    return ret;
}

int DaniTimerCore::setStopTimeMilliSec(unsigned long targetTimeMilliSec)
{
    int ret = TimerCore::Error::INVALID_STATE;
	
	if ( timerStatus == TimerCore::CurrentState::READY )
	{
		targetStopTimeMilliSec = targetTimeMilliSec;
        ret = TimerCore::Error::SUCCESS;
	}
	
	return ret;
}

int DaniTimerCore::start()
{
    int ret = TimerCore::Error::SUCCESS;
    
    if ( timerCountMode == TimerCore::CountMode::COUNTDOWN )
    {
        if ( targetStopTimeMilliSec >= targetStartTimeMilliSec || targetStartTimeMilliSec == 0)
        {
            reset();
            ret = TimerCore::Error::START_FAILED;
        }
    }
    else
    {
        if ( targetStopTimeMilliSec < targetStartTimeMilliSec)
        {
            reset();
            ret = TimerCore::Error::START_FAILED;
        }
    }
    
    if ( timerStatus == TimerCore::CurrentState::STOP ||
        timerStatus == TimerCore::CurrentState::READY)
    {
        startTimeMicroSec = getMeasureTime();
        timerStatus = TimerCore::CurrentState::PROGRESS;
    }
	else if (timerStatus == TimerCore::CurrentState::PAUSE)
	{
		startTimeMicroSec += (getMeasureTime() - pauseTimeMicroSec);
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
		pauseTimeMicroSec = getMeasureTime();
        timerStatus = TimerCore::CurrentState::PAUSE;
        ret = TimerCore::Error::SUCCESS;
    }
    
	return ret;
}

int DaniTimerCore::reset()
{
    int ret = TimerCore::Error::SUCCESS;

	//Times for calculation
	startTimeMicroSec              = 0;
	pauseTimeMicroSec              = 0;
	targetStopTimeMilliSec         = 0;
	targetStartTimeMilliSec        = 0;
	callbackRepeatIntervalMilliSec = 10;
    
	//Preference
	timerStatus = TimerCore::CurrentState::STOP;

	return ret;
}

unsigned long DaniTimerCore::getElapsedTimeSec()
{
	unsigned long ret = (unsigned long)(getElapsedTimeMilliSec() / 1e3);
	
	return ret;
}

unsigned long DaniTimerCore::getElapsedTimeMilliSec()
{
	unsigned long ret = (unsigned long)(getElapsedTimeMicroSec() / 1e3);
	
    return ret;
}

unsigned long DaniTimerCore::getElapsedTimeMicroSec()
{
	long ret = 0;
    
	if ( timerStatus == TimerCore::CurrentState::PROGRESS )
		ret = getMeasureTime() - startTimeMicroSec;
	else if (timerStatus == TimerCore::CurrentState::PAUSE)
		ret = (getMeasureTime() - startTimeMicroSec) - (getMeasureTime() - pauseTimeMicroSec);
	
	if ( timerCountMode == TimerCore::CountMode::COUNTDOWN )
		ret = (targetStartTimeMilliSec * 1e3) - ret;
    else
        ret = (targetStartTimeMilliSec * 1e3) + ret;
    
	return ret > 0 ? ret : 0;
}

int DaniTimerCore::registerCallback(DaniTimerCoreCallbackFunc callback, unsigned long repeatIntervalMilliSec)
{
    int ret = TimerCore::Error::SUCCESS;
	
	if ( callback )
	{
        ret = ( registeredCallBackFunc = std::move(callback) ) ? ret : TimerCore::Error::REGISTER_CALLBACK_FAILED;
		callbackRepeatIntervalMilliSec = repeatIntervalMilliSec;
	}
		
	return ret;
}
