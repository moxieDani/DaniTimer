//
//  main.cpp
//  DaniTimerTest
//
//  Created by daniel-kisoon-kwon on 2016. 8. 27..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//

#include <iostream>
#include "DaniTimer.h"
#include <windows.h>

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Dani Timer test\n";
    
    DaniTimer timer;
    if ( 1 == timer.stop())
        cout << "Invalid sequence! -> call start first!" << endl;
   
    if ( 1 == timer.setStopTimeMilliSec(1000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(1000)"<< endl;

    if ( 0 == timer.start())
        cout << "Dani Timer started!" << endl;
    else
        cout << "Already started!" << endl;
    
    Sleep(1000);
    if ( 1 == timer.setStopTimeMilliSec(7000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(7000)"<< endl;
    
    Sleep(1000);
    if ( 0 == timer.start())
        cout << "Dani Timer started!" << endl;
    else
        cout << "Already started!" << endl;
    cout << "getCurrentTime(sec)" << timer.getCurrentTimeSec() << endl;
    Sleep(1000);
    cout << "getCurrentTime(Millisec)" << timer.getCurrentTimeMilliSec() << endl;
    Sleep(1000);
    cout << "getCurrentTime(Microsec)" << timer.getCurrentTimeMicroSec() << endl;
    
    if ( 1 == timer.setStopTimeMilliSec(5000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(5000)"<< endl;
    
    Sleep(1000);
    if ( 0 == timer.stop())
        cout << "Dani Timer stopped!" << endl;
    else
        cout << "Already stopped!" << endl;
    
    Sleep(1000);
    if ( 0 == timer.stop())
        cout << "Dani Timer stopped!" << endl;
    else
        cout << "Already stopped!" << endl;
    cout << "getElapsedTimeSec(sec)" << timer.getElapsedTimeSec() << endl;
    cout << "getElapsedTimeMilliSec(Millisec)" << timer.getElapsedTimeMilliSec() << endl;
    
    if ( 1 == timer.setStopTimeMilliSec(10000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(10000)"<< endl;
    
    Sleep(1000);
    if ( 1 == timer.setStopTimeMilliSec(5000) )
        cout << "Invalid sequence!(Set stop time failed.) -> Timer is already stopped!" << endl;
    else
        cout << "setStopTimeMilliSec(10000)"<< endl;
    
    Sleep(1000);
    if ( 0 == timer.getCurrentTimeMicroSec() )
        cout << "Invalid sequence! -> Timer is already stopped!" << endl;
	Sleep(1000);
    return 0;
}
