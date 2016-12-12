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
	int setStartTimeMilliSec(unsigned long targetTimeMilliSec);
    int setStopTimeMilliSec(unsigned long targetTimeMilliSec);
    int start();
	int pause();
	int reset();
	unsigned long getElapsedTimeMicroSec();
    unsigned long getElapsedTimeMilliSec();
    unsigned long getElapsedTimeSec();
	int registerCallback(DaniTimerCoreCallbackFunc callback, unsigned long repeatIntervalMilliSec);

private:
	//Functions
    int init();
    unsigned long getMeasureTime();
    static void callbackThreadFunc(void*);
    void timerTaskStart();
    void timerTaskStop();
    
	//Times for calculation
    unsigned long startTimeMicroSec;
	unsigned long pauseTimeMicroSec;
    unsigned long elapsedTimeMicroSec;
    unsigned long targetStopTimeMilliSec;
	unsigned long targetStartTimeMilliSec;
    unsigned long callbackRepeatIntervalMilliSec;
	
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
