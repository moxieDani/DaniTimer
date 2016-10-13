//
//  TAL.hpp
//  DaniTimerTest
//
//  Created by daniel-kisoon-kwon on 2016. 10. 11..
//  Copyright © 2016년 daniel-kisoon-kwon. All rights reserved.
//

#ifndef TAL_H_DEF
#define TAL_H_DEF

class TAL
{
public:
    TAL();
    virtual ~TAL();
    virtual int init() = 0;
    virtual unsigned long getMeasureTime() = 0;

};

#endif /* TAL_H_DEF */
