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
- (int) setStopTimeMilliSec:(unsigned long) targetStopTimeMilliSec;
- (unsigned long) getCurrentTimeMicroSec;
- (unsigned long) getCurrentTimeMilliSec;
- (unsigned long) getCurrentTimeSec;
- (unsigned long) getElapsedTimeMicroSec;
- (unsigned long) getElapsedTimeMilliSec;
- (unsigned long) getElapsedTimeSec;
@end
