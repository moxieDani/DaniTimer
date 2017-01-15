//
//  main.cpp
//  DaniTimerCoreTest
//
//  Created by daniel-kisoon-kwon on 2017. 1. 15..
//  Copyright © 2017년 daniel-kisoon-kwon. All rights reserved.
//
#if defined _WIN32 || _WIN64
	#include <windows.h>
	#define SLEEP(x) Sleep(x*1000)
#else
	#include <unistd.h>
	#define SLEEP(x) sleep(x)
#endif

#include <iostream>
#include "DaniTimerCore.h"

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Dani Timer test\n";
    
    DaniTimerCore timer;
    if ( 0 == timer.setProperty(TimerCore::Property::TIMER_MODE, TimerCore::CountMode::COUNTDOWN) )
		cout << "setTimerMode success!" << endl;
	else
		cout << "setTimerMode failed!" << endl;

    if ( 0 == timer.setProperty(TimerCore::Property::BEGIN_TIME_MILLI_SECOND, 10000) )
		cout << "setProperty(TimerCore::Property::BEGIN_TIME_MILLI_SECOND) success!" << endl;
	else
		cout << "Invalid sequence!(Set start time failed.)"<< endl;
	
	if ( 0 == timer.setProperty(TimerCore::Property::END_TIME_MILLI_SECOND, 2220) )
        cout << "setProperty(TimerCore::Property::END_TIME_MILLI_SECOND) success!" << endl;
    else
        cout << "Invalid sequence!(Set stop time failed.)"<< endl;
    
    if ( 0 == timer.start())
        cout << "========== Dani Timer started! ========== " << endl;
    else
        cout << "Start Error" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    SLEEP(1);
    if ( 0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    if (0 == timer.start())
        cout << "========== Dani Timer started! ========== " << endl;
    else
        cout << "Start Error" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    SLEEP(1);
    if (0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    if (0 == timer.start())
        cout << "========== Dani Timer started! ========== " << endl;
    else
        cout << "Start Error" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    SLEEP(1);
    if (0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    SLEEP(1);
    if (0 == timer.reset())
        cout << "========== Dani Timer reset! ==========" << endl;
    else
        cout << "Reset Error!" << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    SLEEP(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    return 0;
}
