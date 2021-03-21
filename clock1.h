#ifndef __CLOCK1_H_
#define __CLOCK1_H_

#include "clock.h"
#include "ui.h"

class CLOCK1 : protected CLOCK, protected UI
{
private:
    /* data */
    float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0; // Saved H, M, S x & y multipliers
    float sdeg = 0, mdeg = 0, hdeg = 0;
    uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120; // Saved H, M, S x & y coords
    uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

public:
    CLOCK1(/* args */TFT_eSPI &t);
    ~CLOCK1();

    void start();
    void render();
    void restart();
};

#endif