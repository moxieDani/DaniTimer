#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
	int setTimerMode(int timerMode);
	int setStopTimeMilliSec(unsigned long targetTimeMilliSec);
	int setStartTimeMilliSec(unsigned long targetTimeMilliSec);
	int start();
	int pause();
	int resume();
	int stop();
	int reset();
	unsigned long getElapsedTimeMicroSec();
	unsigned long getElapsedTimeMilliSec();
	unsigned long getElapsedTimeSec();
};

#endif /* DANI_TIMER_H_DEF */
