//
//  main.cpp
//  DaniTimerCoreTest
//
//  Created by daniel-kisoon-kwon on 2016. 8. 27..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//

#include <iostream>
#include "DaniTimerCore.h"
#include <unistd.h>

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
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    sleep(1);
    if ( 0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    if (0 == timer.start())
        cout << "========== Dani Timer started! ========== " << endl;
    else
        cout << "Start Error" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    sleep(1);
    if (0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    if (0 == timer.start())
        cout << "========== Dani Timer started! ========== " << endl;
    else
        cout << "Start Error" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    sleep(1);
    if (0 == timer.pause())
        cout << "========== Dani Timer paused! ==========" << endl;
    else
        cout << "Pause Error!" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    sleep(1);
    if (0 == timer.reset())
        cout << "========== Dani Timer reset! ==========" << endl;
    else
        cout << "Reset Error!" << endl;
    
    sleep(1);
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    sleep(1);
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    cout << "getElapsedTimeMicroSec(Microsec)" << timer.getElapsedTimeMicroSec() << endl;
    
    return 0;
}
