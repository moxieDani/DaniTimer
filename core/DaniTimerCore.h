#ifndef DANI_TIMER_CORE_H_DEF
#define DANI_TIMER_CORE_H_DEF

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

namespace timerStatus
{
    enum Enum
    {
        PROGRESS = 0x10000000,
        PAUSE    = 0x10000002,
        STOP     = 0x10000003
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
    int setStopTimeMilliSec(unsigned long targetTimeMilliSec);
    int setCountDownTimeMilliSec(unsigned long targetTimeMilliSec);
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
    timerStatus::Enum timerStatus;
};

#endif /* DANI_TIMER_CORE_H_DEF */
