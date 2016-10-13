//
//  TAL.cpp
//  DaniTimerTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//
#if defined __APPLE__

#include "TALBodyMacOSX.h"

TALBodyMacOSX::TALBodyMacOSX()
{
    
}

TALBodyMacOSX::~TALBodyMacOSX()
{
    
}

/* Private Functions */
int TALBodyMacOSX::init()
{
    measureClock = 0;
    measureTime.tv_nsec = 0;
    measureTime.tv_sec = 0;
    return 0;
}

unsigned long TALBodyMacOSX::getMeasureTime()
{
    unsigned long ret = 0;
    
    if ( KERN_SUCCESS == host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &measureClock) )
    {
        if ( KERN_SUCCESS == clock_get_time(measureClock, &measureTime) )
            ret = ( ( measureTime.tv_sec * 1e9 ) + measureTime.tv_nsec ) / 1e3;
        mach_port_deallocate(mach_task_self(), measureClock);
    }
    
    return ret;
}

#endif /* __APPLE__ */
