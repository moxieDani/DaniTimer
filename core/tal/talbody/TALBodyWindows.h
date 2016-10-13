//
//  TAL.hpp
//  DaniTimerTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//

#if defined _WIN32 || _WIN64

#include<Windows.h>
#include "TAL.h"

class TALBodyWindows : public TAL
{
public:
    TALBodyWindows();
    ~TALBodyWindows();
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER measureTime;
protected:
    int init();
    unsigned long getMeasureTime();
    
};

#endif /* _WIN32 || _WIN64 */
