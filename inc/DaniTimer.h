#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#include<Windows.h>

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
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER stopCount;
	double startTimeMicroSec;
	double stopTimeMicroSec;
	double currentTimeMicroSec;
	double elapsedTimeMicroSec;
};

#endif