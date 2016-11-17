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
    
    if ( 1 == timer.setStopTimeMilliSec(10000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(10000)"<< endl;
    
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
    if ( 0 == timer.stop())
        cout << "========== Dani Timer stopped! ==========" << endl;
    else
        cout << "Stop Error!" << endl;
    
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
    if (0 == timer.stop())
        cout << "========== Dani Timer stopped! ==========" << endl;
    else
        cout << "Stop Error!" << endl;
    
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
    if (0 == timer.stop())
        cout << "========== Dani Timer stopped! ==========" << endl;
    else
        cout << "Stop Error!" << endl;
    
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
