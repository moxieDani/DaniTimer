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

typedef std::function<int(int)> DaniTimerCallbackFunc;

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
    int registerCallack(DaniTimerCallbackFunc callback);
	int start();
	int stop();
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
    
    DaniTimerCallbackFunc callBackFunc;
	unsigned long startTimeSec;
	unsigned long elapsedTimeSec;
};

#endif