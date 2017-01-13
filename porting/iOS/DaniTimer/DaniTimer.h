//
//  DaniTimer.h
//  DaniTimer
//
//  Created by daniel-kisoon-kwon on 2016. 11. 10..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//
#ifndef DANITIMER_H_DEF
#define DANITIMER_H_DEF

#import <UIKit/UIKit.h>
#import "DaniTimerProperty.h"

@protocol onTimeDelegate <NSObject>

@optional
-(void)onTime:(NSNumber*)milliSec;

@end

@interface DaniTimer: NSObject

@property (nonatomic,weak) id<onTimeDelegate> delegate;

- (int) start;
- (int) pause;
- (int) reset;
- (int) setBeginTimeMilliSec:(unsigned long long) targetTimeMilliSec;
- (int) setEndTimeMilliSec:(unsigned long long) targetStopTimeMilliSec;
- (unsigned long long) getElapsedTimeMicroSec;
- (unsigned long long) getElapsedTimeMilliSec;
- (unsigned long long) getElapsedTimeSec;
- (int) setOnTimeDelegate:(id<onTimeDelegate>)delegate withRepeatInterval:(unsigned long long)targetTimeMilliSec;

template <typename PropertyValue>
- (int) setProperty:(int)propertyType proertyValue:(PropertyValue) value;
@end

#endif
