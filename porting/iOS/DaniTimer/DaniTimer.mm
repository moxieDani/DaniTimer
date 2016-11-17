//
//  DaniTimer.m
//  DaniTimer
//
//  Created by daniel-kisoon-kwon on 2016. 11. 10..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DaniTimer.h"
#import "DaniTimerCore.h"

@implementation DaniTimer {
    DaniTimerCore *timerCore;
}

#pragma mark -
#pragma mark Construct

- (instancetype) init
{
    self = [super init];
    
    if( self != nil )
    {
        timerCore = new DaniTimerCore();
    }
    
    return self;
}

#pragma mark -
#pragma mark Public APIs

- (int) start {
    int ret = timerCore->start();
    return ret;
}

- (int) stop {
    int ret = timerCore->stop();
    return ret;
}

- (int) reset {
    int ret = timerCore->reset();
    return ret;
}

- (int) setStopTimeMilliSec:(unsigned long) targetStopTimeMilliSec {
    int ret = timerCore->setStopTimeMilliSec(targetStopTimeMilliSec);
    return ret;
}

- (int) setStartTimeMilliSec:(unsigned long) targetStopTimeMilliSec {
    int ret = timerCore->setStartTimeMilliSec(targetStopTimeMilliSec);
    return ret;
}

- (unsigned long) getElapsedTimeMicroSec {
    unsigned long ret = timerCore->getElapsedTimeMicroSec();
    return ret;
}

- (unsigned long) getElapsedTimeMilliSec {
    unsigned long ret = timerCore->getElapsedTimeMilliSec();
    return ret;
}

- (unsigned long) getElapsedTimeSec {
    unsigned long ret = timerCore->getElapsedTimeSec();
    return ret;
}

#pragma mark -
#pragma mark Destroy

- (void) dealloc
{
    if ( timerCore )
        delete timerCore;
}

@end
