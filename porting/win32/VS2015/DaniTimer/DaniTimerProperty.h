//
//  DaniTimerProperty.h
//  DaniTimer
//
//  Created by daniel-kisoon-kwon on 2016. 11. 10..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//

#ifndef DANI_TIMER_PROPERTY_H
#define DANI_TIMER_PROPERTY_H

typedef enum {
	TIMER_MODE                            = 0x30000001,
    
	BEGIN_TIME_MILLI_SECOND               = 0x30000002,
    
	END_TIME_MILLI_SECOND                 = 0x30000003,
    
    ON_TIME_REAPEAT_INTERVAL_MILLI_SECOND = 0x30000004
    
} DaniProperty;

#endif /* DANI_TIMER_PROPERTY_H */
