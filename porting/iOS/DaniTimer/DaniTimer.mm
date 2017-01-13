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

@interface DaniTimer() <onTimeDelegate>


@property (nonatomic) DaniTimerCore *timerCore;
@property (nonatomic, strong) NSThread *t;
@property (nonatomic) unsigned long long callbackRepeatIntervalMilliSec;
@property (nonatomic) unsigned long long targetStopTimeMilliSec;
@property (nonatomic) unsigned long long targetStartTimeMilliSec;

@end

@implementation DaniTimer

#pragma mark -
#pragma mark Construct
- (instancetype) init
{
    self = [super init];
    
    if( self != nil )
    {
        self.timerCore = new DaniTimerCore();
		self.callbackRepeatIntervalMilliSec = 10;
		self.targetStopTimeMilliSec = 0;
		self.targetStartTimeMilliSec = 0;
    }
    [self setProperty:0 proertyValue:100];
    return self;
}

#pragma mark -
#pragma mark Public APIs

- (int) start {
    int ret = self.timerCore->start();
	[self timerTaskStart];
    return ret;
}

- (int) pause {
    int ret = self.timerCore->pause();
    return ret;
}

- (int) reset {
    int ret = self.timerCore->reset();
	self.targetStopTimeMilliSec = 0;
	self.targetStartTimeMilliSec = 0;
    return ret;
}

- (int) setBeginTimeMilliSec:(unsigned long long)  targetTimeMilliSec {
	self.targetStartTimeMilliSec = targetTimeMilliSec;
	int ret = self.timerCore->setBeginTimeMilliSec(self.targetStartTimeMilliSec);
	return ret;
}

- (int) setEndTimeMilliSec:(unsigned long long) targetTimeMilliSec {
	self.targetStopTimeMilliSec = targetTimeMilliSec;
    int ret = self.timerCore->setEndTimeMilliSec(self.targetStopTimeMilliSec);
    return ret;
}

- (unsigned long long) getElapsedTimeMicroSec {
    unsigned long long ret = self.timerCore->getElapsedTimeMicroSec();
    return ret;
}

- (unsigned long long) getElapsedTimeMilliSec {
    unsigned long long ret = self.timerCore->getElapsedTimeMilliSec();
    return ret;
}

- (unsigned long long) getElapsedTimeSec {
    unsigned long long ret = self.timerCore->getElapsedTimeSec();
    return ret;
}

- (int) setOnTimeDelegate:(id<onTimeDelegate>)delegate withRepeatInterval:(unsigned long long)targetTimeMilliSec {
	int ret = TimerCore::Error::SUCCESS;
	
	self.delegate = delegate;
	if( [self.delegate respondsToSelector:@selector(onTime:)] == NO ) {
		ret = TimerCore::Error::SET_ONTIME_DELIGATE_FAILED;
	}
	
	if ( targetTimeMilliSec > 0 ) {
		self.callbackRepeatIntervalMilliSec = targetTimeMilliSec;
	}
	
	return ret;
}

- (void) callbackThreadFunc {
	unsigned long long currentTime = 0;
	unsigned long long newCurrentTime = 0;
	
	if ( self.t )
	{
		while ( [self getCurrentState] != TimerCore::CurrentState::STOP )
		{
			if ([self getCurrentState] == TimerCore::CurrentState::PAUSE ||
				[self getCurrentState] == TimerCore::CurrentState::READY)
				continue;
			
			newCurrentTime = [self getElapsedTimeMilliSec];
			
			if ( currentTime/1e3 == newCurrentTime/1e3 )
				continue;
			
			if ( self.delegate )
			{
				if ( ( newCurrentTime % self.callbackRepeatIntervalMilliSec ) == 0 )
					if ( [self.delegate respondsToSelector:@selector(onTime:)] )
						[self.delegate performSelector:@selector(onTime:) withObject:[NSNumber numberWithUnsignedLongLong:newCurrentTime]];
			}
			
			if ( ([self getCurrentState] == TimerCore::CountMode::COUNTUP && newCurrentTime > self.targetStopTimeMilliSec) ||
				([self getCurrentState] == TimerCore::CountMode::COUNTDOWN && newCurrentTime < self.targetStopTimeMilliSec) )
				[self reset];
			
			currentTime = newCurrentTime;
		}
	}
}

- (void) timerTaskStart {
	self.t = [[NSThread alloc] initWithTarget:self selector:@selector(callbackThreadFunc) object:nil];
	if ( self.t )
		[self.t start];
}

- (void) timerTaskStop {
	if ( [self.t isCancelled] == NO){
		[self.t cancel];
		self.t = nil;
	}
}

- (int) getCurrentState {
	return self.timerCore->getCurrentState();
}

#pragma mark -
#pragma mark Destroy

- (void) dealloc
{
	if ( self.timerCore ) {
        delete self.timerCore;
		self.timerCore = nullptr;
	}
	[self timerTaskStop];
}

@end



