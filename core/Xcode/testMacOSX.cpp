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
int callBackTest( unsigned long a );

int callBackTest( unsigned long a )
{
    printf("[CallbackTest] Current time(%lu)\n", a);
    return 0;
}

int main(int argc, const char * argv[]) {
    cout << "Dani Timer test\n";
    
    DaniTimerCore timer;
    if ( 0 == timer.registerCallback(callBackTest, 1000))
        cout << "Callback registration success!" << endl;
    else
        cout << "Callback registration failed!" << endl;
	
	if ( 0 == timer.setTimerMode(0) )
		cout << "setTimerMode success!" << endl;
	else
		cout << "Callback setTimerMode failed!" << endl;

	if ( 0 == timer.setStartTimeMilliSec(10000) )
		cout << "setStartTimeMilliSec success!" << endl;
	else
		cout << "Invalid sequence!(Set start time failed.)"<< endl;
	
	if ( 0 == timer.setStopTimeMilliSec(13000) )
        cout << "setStopTimeMilliSec success!" << endl;
    else
        cout << "Invalid sequence!(Set stop time failed.)"<< endl;
    
    if ( 0 == timer.start())
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
