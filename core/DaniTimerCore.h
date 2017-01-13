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
	int setBeginTimeMilliSec(unsigned long long targetTimeMilliSec);
    int setEndTimeMilliSec(unsigned long long targetTimeMilliSec);
    int start();
	int pause();
	int reset();
	unsigned long long getElapsedTimeMicroSec();
    unsigned long long getElapsedTimeMilliSec();
    unsigned long long getElapsedTimeSec();
	int getCurrentState();

	template <typename PropertyValue>
	int setProperty(int propertyType, PropertyValue value);

private:
	//Functions
    int init();
    unsigned long long getMeasureTime();
    static void callbackThreadFunc(void*);
    void timerTaskStart();
    void timerTaskStop();
    
	//Times for calculation
    unsigned long long measuredStartPoint;
	unsigned long long measuredPausePoint;
    unsigned long long elapsedTimeMicroSec;
    unsigned long long targetEndTimeMilliSec;
	unsigned long long targetBeginTimeMilliSec;
    unsigned long long callbackRepeatIntervalMilliSec;
	
	//Callback
    std::thread *timerTask;
	
	//Preference
	int timerCountMode;
	int timerStatus;
    
    //Timer Adaptation Layer
    TAL *tal;
};

#endif /* DANI_TIMER_CORE_H_DEF */
