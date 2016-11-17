//
//  TAL.hpp
//  DaniTimerCoreTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//

#if defined __linux__

#include<sys/time.h>
#include "TAL.h"

class TALBodyLinux : public TAL
{
public:
    TALBodyLinux();
    ~TALBodyLinux();
private:
    struct timespec measureTime;
protected:
    int init();
    unsigned long getMeasureTime();
};

#endif /* __linux__ */
