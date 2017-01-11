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
@protocol OnTimeDelegate <NSObject>

@optional
-(void)onTime:(NSNumber*)milliSec;

@end

@interface DaniTimer: NSObject

@property (nonatomic,weak) id<OnTimeDelegate> delegate;

- (int) start;
- (int) pause;
- (int) reset;
- (int) setStopTimeMilliSec:(unsigned long long) targetStopTimeMilliSec;
- (int) setStartTimeMilliSec:(unsigned long long) targetTimeMilliSec;
- (unsigned long long) getElapsedTimeMicroSec;
- (unsigned long long) getElapsedTimeMilliSec;
- (unsigned long long) getElapsedTimeSec;
- (int) setOnTimeDelegate:(id<OnTimeDelegate>)delegate withRepeatInterval:(unsigned long long)milliSec;
@end

#endif
