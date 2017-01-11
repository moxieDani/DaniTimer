//
//  TAL.hpp
//  DaniTimerCoreTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//
#if defined __APPLE__

#include <mach/clock.h>
#include <mach/mach.h>
#include "TAL.h"

class TALBodyMacOSX : public TAL
{
public:
    TALBodyMacOSX();
    ~TALBodyMacOSX();
private:
    clock_serv_t measureClock;
    mach_timespec_t measureTime;
protected:
    int init();
    unsigned long long getMeasureTime();

};
#endif /* __APPLE__ */
