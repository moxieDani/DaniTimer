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
	int ret = 1;
	
	//Times for calculation
	startTimeMicroSec              = 0;
	pauseTimeMicroSec              = 0;
	elapsedTimeMicroSec            = 0;
	targetStopTimeMilliSec         = 0;
	callbackRepeatIntervalMilliSec = 0;
	
	//Callback
	callBackThread         = nullptr;
	registeredCallBackFunc = nullptr;
	
	//Preference
    timerCountMode = TimerCore::CountMode::COUNTUP;
	timerStatus    = TimerCore::CurrentState::STOP;
	
	//Timer Adaptation Layer
	tal = new TALBODY_CLASS;
	ret = tal->init();

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
	
	if ( t && t->registeredCallBackFunc )
	{
        while ( t->timerStatus != TimerCore::CurrentState::STOP )
		{
			if (t->timerStatus == TimerCore::CurrentState::PAUSE)
				continue;
			
			newCurrentTime = t->getElapsedTimeMilliSec();
			
			if ( currentTime/1e3 == newCurrentTime/1e3 )
				continue;
			
			if ( ( newCurrentTime % t->callbackRepeatIntervalMilliSec ) == 0 )
				t->registeredCallBackFunc(newCurrentTime);

			if (newCurrentTime > t->targetStopTimeMilliSec)
            {
                t->stop();
                t->timerStatus = TimerCore::CurrentState::STOP;
            }
			currentTime = newCurrentTime;
		}
	}
}

/* Public Functions */
DaniTimerCore::DaniTimerCore()
{
	init();
}

DaniTimerCore::~DaniTimerCore()
{
	reset();

	if ( registeredCallBackFunc )
		registeredCallBackFunc = nullptr;
	
	if ( tal )
		delete tal;
}

int DaniTimerCore::setTimerMode(int timerMode)
{
	int ret = 1;
	
	if ( timerStatus == TimerCore::CurrentState::STOP )
	{
		timerCountMode = timerMode;
		ret = 0;
	}
	
	return ret;
}

int DaniTimerCore::setStopTimeMilliSec(unsigned long targetTimeMilliSec)
{
	int ret = 1;
	
	if ( timerStatus == TimerCore::CurrentState::STOP )
	{
		targetStopTimeMilliSec = targetTimeMilliSec;
		ret = 0;
	}
	
	return ret;
}

int DaniTimerCore::setStartTimeMilliSec(unsigned long targetTimeMilliSec)
{
	int ret = 1;
	
	if ( timerStatus == TimerCore::CurrentState::STOP )
	{
		targetStopTimeMilliSec = targetTimeMilliSec;
		ret = 0;
	}
	
	return ret;
}


int DaniTimerCore::start()
{
    int ret = 1;
	
    if ( timerStatus == TimerCore::CurrentState::STOP )
    {
        startTimeMicroSec = getMeasureTime();
        timerStatus = TimerCore::CurrentState::PROGRESS;
        callBackThread = new std::thread (&DaniTimerCore::callbackThreadFunc, this);
        ret = 0;
    }
	else if (timerStatus == TimerCore::CurrentState::PAUSE)
	{
		startTimeMicroSec += (getMeasureTime() - pauseTimeMicroSec);
		timerStatus = TimerCore::CurrentState::PROGRESS;
		ret = 0;
	}
    
    return ret;
}

int DaniTimerCore::stop()
{
    int ret = 1;
	
    if ( timerStatus == TimerCore::CurrentState::PROGRESS )
    {
		pauseTimeMicroSec = getMeasureTime();
        elapsedTimeMicroSec = getMeasureTime() - startTimeMicroSec;
        timerStatus = TimerCore::CurrentState::PAUSE;
        ret = 0;
    }
    
	return ret;
}

int DaniTimerCore::reset()
{
	int ret = 1;

	//Times for calculation
	startTimeMicroSec              = 0;
	pauseTimeMicroSec              = 0;
	elapsedTimeMicroSec            = 0;
	targetStopTimeMilliSec         = 0;
	callbackRepeatIntervalMilliSec = 0;

	//Callback thread
	if (callBackThread)
	{
		callBackThread->join();
		delete callBackThread;
		callBackThread = nullptr;
	}

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
	unsigned long ret = 0;
	if (timerStatus == TimerCore::CurrentState::PROGRESS)
		ret = getMeasureTime() - startTimeMicroSec;
	else if (timerStatus == TimerCore::CurrentState::PAUSE)
		ret = (getMeasureTime() - startTimeMicroSec) - (getMeasureTime() - pauseTimeMicroSec);

	return ret;
}

int DaniTimerCore::registerCallback(DaniTimerCoreCallbackFunc callback, unsigned long repeatIntervalMilliSec)
{
	int ret = 1;
	
	if ( callback )
	{
		ret = ( registeredCallBackFunc = std::move(callback) ) ? 0 : 1;
		callbackRepeatIntervalMilliSec = repeatIntervalMilliSec;
	}
		
	return ret;
}
