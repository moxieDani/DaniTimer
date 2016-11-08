#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#include <functional>
#include <thread>
#include "TAL.h"

typedef std::function<int(unsigned long)> DaniTimerCoreCallbackFunc;

namespace callFrequency
{
    enum Enum
    {
        NONE = 0,
        CALL_EVERYTIME = 0,
        CALL_ONCE,
        LAST_VALUE = CALL_ONCE
    };
}

class DaniTimerCore
{
public:
	DaniTimerCore();
	~DaniTimerCore();
    int registerCallback(DaniTimerCoreCallbackFunc callback, callFrequency::Enum callType, unsigned long userSetTimeMilliSec);
	int start();
	int stop();
    int setStopTimeMilliSec(unsigned long targetStopTimeMilliSec);
	unsigned long getCurrentTimeMicroSec();
    unsigned long getCurrentTimeMilliSec();
    unsigned long getCurrentTimeSec();
	unsigned long getElapsedTimeMicroSec();
    unsigned long getElapsedTimeMilliSec();
    unsigned long getElapsedTimeSec();

private:
    int init();
    unsigned long getMeasureTime();
    
    TAL *tal;
    unsigned long startTimeSec;
    unsigned long targetStopTimeMilliSec;
    unsigned long elapsedTimeSec;
    DaniTimerCoreCallbackFunc callBackFunc;
    int callType;
    unsigned long userSetTimeMilliSec;
    std::thread *callBackThread;
    static void callbackThreadFunc(void*);
};

#endif /* DANI_TIMER_H_DEF */
