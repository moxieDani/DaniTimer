#ifndef DANI_TIMER_H_DEF
#define DANI_TIMER_H_DEF

#include <functional>
#include <thread>

typedef std::function<int(unsigned long long)> onTimeFunction;

class DaniTimer
{
public:
	DaniTimer();
	~DaniTimer();
	int start();
	int pause();
	int reset();
	unsigned long long getElapsedTimeMicroSec();
	unsigned long long getElapsedTimeMilliSec();
	unsigned long long getElapsedTimeSec();
	int setProperty(int type, unsigned long long value);
	int setOnTime(onTimeFunction func);

private:
	void timerTaskStart();
	void timerTaskStop();
	static void onTimeThreadFunc(void* data);
	int getCurrentState();

	std::thread *timerTask;
	onTimeFunction onTime;
	unsigned long long onTimeRepeatIntervalMilliSec;
};

#endif /* DANI_TIMER_H_DEF */
