//
//  DaniTimer.h
//  DaniTimer
//
//  Created by daniel-kisoon-kwon on 2016. 11. 10..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DaniTimer: NSObject
- (int) start;
- (int) stop;
- (int) reset;
- (int) setStopTimeMilliSec:(unsigned long) targetStopTimeMilliSec;
- (int) setStartTimeMilliSec:(unsigned long) targetTimeMilliSec;
- (unsigned long) getElapsedTimeMicroSec;
- (unsigned long) getElapsedTimeMilliSec;
- (unsigned long) getElapsedTimeSec;
@end
