#ifndef DANI_TIMER_CORE_H_DEF
#define DANI_TIMER_CORE_H_DEF

#include <functional>
#include "DaniTimerCoreTypes.h"
#include "TAL.h"

class DaniTimerCore
{
public:
	DaniTimerCore();
	~DaniTimerCore();
    int start();
	int pause();
	int reset();
	unsigned long long getElapsedTimeMicroSec();
    unsigned long long getElapsedTimeMilliSec();
    unsigned long long getElapsedTimeSec();
	int getCurrentState();
    int setProperty(int type, unsigned long long value);
    
private:
	//Functions
    int init();
    unsigned long long getMeasureTime();
    
	//Times for calculation
    unsigned long long measuredStartPoint;
	unsigned long long measuredPausePoint;
    unsigned long long elapsedTimeMicroSec;
    
	//Preference
	int timerCountMode;
	int timerStatus;
    unsigned long long targetEndTimeMilliSec;
    unsigned long long targetBeginTimeMilliSec;
    
    //Timer Adaptation Layer
    TAL *tal;
};

#endif /* DANI_TIMER_CORE_H_DEF */
