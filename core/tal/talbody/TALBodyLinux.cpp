//
//  TAL.cpp
//  DaniTimerCoreTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//
#if defined __linux__

#include "TALBodyLinux.h"

TALBodyLinux::TALBodyLinux()
{
    
}

TALBodyLinux::~TALBodyLinux()
{
    
}

/* Private Functions */
int TALBodyLinux::init()
{
    measureTime.tv_nsec = 0;
    measureTime.tv_sec = 0;
    return 0;
}

unsigned long TALBodyLinux::getMeasureTime()
{
    unsigned long ret = 0;
    
    if( 0 == clock_gettime(CLOCK_MONOTONIC, &measureTime) )
        ret = ( ( measureTime.tv_sec * 1e9 ) + measureTime.tv_nsec ) / 1e3;
    
    return ret;
}

#endif /* __linux__ */
