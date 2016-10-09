#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#if defined _WIN32 || _WIN64
#include<Windows.h>
#elif defined __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include<sys/time.h>
#endif

#include <functional>
#include <thread>

typedef std::function<int(unsigned long)> DaniTimerCallbackFunc;

namespace callFrequency
{
    enum Enum
    {
        callTypeFirst = 0,
        CALL_FUNCTION_EVERYTIME = 0,
        CALL_FUNCTION_ONCE,
        callTypeLast = CALL_FUNCTION_ONCE
    };
}

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
    int registerCallback(DaniTimerCallbackFunc callback, callFrequency::Enum callType, unsigned long userSetTimeMilliSec);
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
    
#if defined _WIN32 || _WIN64
	LARGE_INTEGER frequency;
	LARGE_INTEGER measureTime;
#elif defined __MACH__
    clock_serv_t measureClock;
    mach_timespec_t measureTime;
#else
    struct timespec measureTime;
#endif
    unsigned long startTimeSec;
    unsigned long targetStopTimeMilliSec;
    unsigned long elapsedTimeSec;
    DaniTimerCallbackFunc callBackFunc;
    int callType;
    unsigned long userSetTimeMilliSec;
    
protected:
    std::thread *callBackThread;
    static void callbackThreadFunc(void*);
};

#endif
