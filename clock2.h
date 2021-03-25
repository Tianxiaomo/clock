#ifndef __CLOCK2_H_
#define __CLOCK2_H_

#include "clock.h"
#include "ui.h"

class CLOCK2 : protected CLOCK, public UI
{
private:
    /* data */
    byte omm = 99, oss = 99;
    byte xcolon = 0, xsecs = 0;
    unsigned int colour = 0;

    // 温湿度
    float temLast = -100;
    float rhLast = -100;

public:
    CLOCK2(/* args */ TFT_eSPI &t);
    ~CLOCK2();

    void start(void);
    void render(void);
    void restart(void);
};

#endif
