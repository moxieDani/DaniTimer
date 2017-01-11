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

@interface DaniTimer() <OnTimeDelegate>

@property (nonatomic) DaniTimerCore *timerCore;
@property (nonatomic, strong) NSThread *t;
@property (nonatomic) unsigned long long onTImeIntervalMilliSec;
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
		self.onTImeIntervalMilliSec = 10;
		self.targetStopTimeMilliSec = 0;
		self.targetStartTimeMilliSec = 0;
    }
    
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

- (int) setStopTimeMilliSec:(unsigned long long) targetTimeMilliSec {
	self.targetStopTimeMilliSec = targetTimeMilliSec;
    int ret = self.timerCore->setStopTimeMilliSec(self.targetStopTimeMilliSec);
    return ret;
}

- (int) setStartTimeMilliSec:(unsigned long long) targetTimeMilliSec {
	self.targetStartTimeMilliSec = targetTimeMilliSec;
    int ret = self.timerCore->setStartTimeMilliSec(self.targetStartTimeMilliSec);
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

- (int) setOnTimeDelegate:(id<OnTimeDelegate>)delegate withRepeatInterval:(unsigned long long)milliSec {
	int ret = TimerCore::Error::SUCCESS;
	
	self.delegate = delegate;
	if( [self.delegate respondsToSelector:@selector(onTime:)] == NO ) {
		ret = TimerCore::Error::SET_ONTIME_DELIGATE_FAILED;
	}
	
	if ( milliSec > 0 ) {
		self.onTImeIntervalMilliSec = milliSec;
	}
	
	return ret;
}

- (void) onTimeThreadFunc {
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
				if ( ( newCurrentTime % self.onTImeIntervalMilliSec ) == 0 )
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
	self.t = [[NSThread alloc] initWithTarget:self selector:@selector(onTimeThreadFunc) object:nil];
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
