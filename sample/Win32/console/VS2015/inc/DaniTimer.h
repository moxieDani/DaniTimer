#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
    int start();
	int stop();
    int setStopTimeMilliSec(unsigned long targetStopTimeMilliSec);
	unsigned long getCurrentTimeMicroSec();
    unsigned long getCurrentTimeMilliSec();
    unsigned long getCurrentTimeSec();
	unsigned long getElapsedTimeMicroSec();
    unsigned long getElapsedTimeMilliSec();
    unsigned long getElapsedTimeSec();

};

#endif /* DANI_TIMER_H_DEF */
