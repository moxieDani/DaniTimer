//
//  TAL.hpp
//  DaniTimerCore
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
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
    unsigned long long getMeasureTime();
    
};

#endif /* _WIN32 || _WIN64 */
