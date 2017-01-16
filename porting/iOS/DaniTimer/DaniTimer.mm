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
#import "DaniTimerTypes.h"

@interface DaniTimer() <onTimeDelegate>


@property (nonatomic) DaniTimerCore *timerCore;
@property (nonatomic, strong) NSThread *t;
@property (nonatomic) unsigned long long onTimeRepeatIntervalMilliSec;

@end

@implementation DaniTimer

#pragma mark -
#pragma mark Construct
- (instancetype) init
{
	self = [super init];
	
	if( self != nil )
	{
		self.t = nil;
		self.timerCore = new DaniTimerCore();
		self.onTimeRepeatIntervalMilliSec = 10;
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
	[self timerTaskStop];
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

- (int) setOnTimeDelegate:(id<onTimeDelegate>)delegate {
	int ret = TimerType::Error::SUCCESS;
	
	self.delegate = delegate;
	if( [self.delegate respondsToSelector:@selector(onTime:)] == NO ) {
		ret = TimerType::Error::SET_ONTIME_DELIGATE_FAILED;
	}
	
	return ret;
}

- (int) setProperty:(int)propertyType proertyValue:(NSInteger)value {
	int ret = TimerCore::Error::SUCCESS;
	
	switch (propertyType) {
		case ON_TIME_REAPEAT_INTERVAL_MILLI_SECOND:
			self.onTimeRepeatIntervalMilliSec = (value > 0) ? value : 10;
			if ( value <= 0 )
				ret = TimerCore::Error::SET_PROPERTY_FAILED;
			break;
		default:
			ret = self.timerCore->setProperty(propertyType, (unsigned long long)value);
			break;
	}
	return ret;
}

#pragma mark -
#pragma mark Private APIs
- (void) onTimeThreadFunc {
	unsigned long long currentTime = 0;
	unsigned long long newCurrentTime = 0;
	
	while ( [self getCurrentState] != TimerCore::CurrentState::STOP )
	{
		if ([self getCurrentState] == TimerCore::CurrentState::PAUSE ||
			[self getCurrentState] == TimerCore::CurrentState::READY)
			continue;
		
		newCurrentTime = [self getElapsedTimeMilliSec];
		
		if ( currentTime/1e3 == newCurrentTime/1e3 )
			continue;
		
		if ( self.delegate && [self.delegate respondsToSelector:@selector(onTime:)] )
		{
			if ( ( newCurrentTime % self.onTimeRepeatIntervalMilliSec ) == 0 )
				[self.delegate performSelector:@selector(onTime:) withObject:[NSNumber numberWithUnsignedLongLong:newCurrentTime]];
		}
		currentTime = newCurrentTime;
	}
}

- (void) timerTaskStart {
	if ( self.t == nil )
		self.t = [[NSThread alloc] initWithTarget:self selector:@selector(onTimeThreadFunc) object:nil];
	if ( self.t )
		[self.t start];
}

- (void) timerTaskStop {
	if ( [self.t isCancelled] == NO ){
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



