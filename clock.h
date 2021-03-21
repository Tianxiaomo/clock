#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <Arduino.h>

class CLOCK
{
protected:
    /* data */
    uint8_t hh,mm,ss;  // Get H, M, S from compile time

public:
    CLOCK(/* args */);
    ~CLOCK();
};



#endif