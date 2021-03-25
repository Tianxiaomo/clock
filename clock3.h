#ifndef __CLOCK3_H_
#define __CLOCK3_H_

#include "clock.h"
#include "ui.h"
#include "img.h"

class CLOCK3 : protected CLOCK, public UI
{
private:
    /* data */
    byte omm = 99, oss = 99;
    byte xcolon = 0, xsecs = 0;
    uint8_t osx, osy, gx, gy; // x,y位置，xy间隔

    uint8_t h1, h2, m1, m2, s1, s2;

    uint8_t count ;
    // 温湿度
    float temLast = -100;
    float rhLast = -100;

public:
    CLOCK3(/* args */ TFT_eSPI &t, uint8_t ox = 10, uint8_t oy = 10, uint8_t x = 10, uint8_t y = 10);
    ~CLOCK3();

    void start(void);
    void render(void);
    void restart(void);
};

#endif
