#ifndef DANI_TIMER_CORE_H_DEF
#define DANI_TIMER_CORE_H_DEF

#include <functional>
#include <thread>
#include "DaniTimerCoreTypes.h"
#include "TAL.h"

class DaniTimerCore
{
public:
	DaniTimerCore();
	~DaniTimerCore();
	int setTimerMode(int timerMode);
	int setStartTimeMilliSec(unsigned long long targetTimeMilliSec);
    int setStopTimeMilliSec(unsigned long long targetTimeMilliSec);
    int start();
	int pause();
	int reset();
	unsigned long long getElapsedTimeMicroSec();
    unsigned long long getElapsedTimeMilliSec();
    unsigned long long getElapsedTimeSec();
	int registerCallback(DaniTimerCoreCallbackFunc callback, unsigned long long repeatIntervalMilliSec);
	int getCurrentState();

private:
	//Functions
    int init();
    unsigned long long getMeasureTime();
    static void callbackThreadFunc(void*);
    void timerTaskStart();
    void timerTaskStop();
    
	//Times for calculation
    unsigned long long startTimeMicroSec;
	unsigned long long pauseTimeMicroSec;
    unsigned long long elapsedTimeMicroSec;
    unsigned long long targetStopTimeMilliSec;
	unsigned long long targetStartTimeMilliSec;
    unsigned long long callbackRepeatIntervalMilliSec;
	
	//Callback
    std::thread *timerTask;
	DaniTimerCoreCallbackFunc registeredCallBackFunc;
	
	//Preference
	int timerCountMode;
	int timerStatus;
    
    //Timer Adaptation Layer
    TAL *tal;
};

#endif /* DANI_TIMER_CORE_H_DEF */
