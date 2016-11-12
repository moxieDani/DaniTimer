//
//  TAL.cpp
//  DaniTimerCore
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//
#if defined _WIN32 || _WIN64

#include "TALBodyWindows.h"

TALBodyWindows::TALBodyWindows()
{
    
}

TALBodyWindows::~TALBodyWindows()
{
    
}

/* Private Functions */
int TALBodyWindows::init()
{
    QueryPerformanceFrequency(&frequency);
    return 0;
}

unsigned long TALBodyWindows::getMeasureTime()
{
    unsigned long ret = 0;
    
    measureTime.QuadPart = 0;
    if ( QueryPerformanceCounter(&measureTime) )
        ret = (unsigned long)(double(measureTime.QuadPart) / (double(frequency.QuadPart)) * 1e6);
    
    return ret;
}

#endif /* _WIN32 || _WIN64 */
