#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#ifdef WIN32
#include<Windows.h>
#else
#endif

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
	int start();
	int stop();
	double getCurrentTimeMicroSec();
	double getElapsedTimeMicroSec();

private:
#ifdef WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER stopCount;
#else
#endif
	double startTimeMicroSec;
	double stopTimeMicroSec;
	double currentTimeMicroSec;
	double elapsedTimeMicroSec;
};

#endif