#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#if defined WIN32
#include<Windows.h>
#elif defined __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include<sys/time.h>
#endif

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
	int start();
	int stop();
	long double getCurrentTimeMicroSec();
    long double getCurrentTimeMilliSec();
    long double getCurrentTimeSec();
	long double getElapsedTimeMicroSec();
    long double getElapsedTimeMilliSec();
    long double getElapsedTimeSec();

private:
    long double getMeasureTime();
#if defined WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER measureTime;
#elif defined __MACH__
    clock_serv_t measureClock;
    mach_timespec_t measureTime;
#else
    struct timespec measureTime;
#endif
	long double startTimeSec;
	long double stopTimeSec;
	long double currentTimeSec;
	long double elapsedTimeSec;
};

#endif