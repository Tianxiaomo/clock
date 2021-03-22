#ifndef __CLOCK1_H_
#define __CLOCK1_H_

#include "clock.h"
#include "ui.h"

class CLOCK1 : protected CLOCK, public UI
{
private:
    /* data */
    float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0; // Saved H, M, S x & y multipliers
    float sdeg = 0, mdeg = 0, hdeg = 0;
    uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120; // Saved H, M, S x & y coords
    uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

    // 秒针，分针，时针，边框，表盘颜色
    uint16_t sColor,mColor,hColor,borderColor,padColor;

public:
    // CLOCK1(/* args */TFT_eSPI &t);
    CLOCK1(/* args */TFT_eSPI &t,uint16_t sC = TFT_RED,uint16_t mC=TFT_WHITE,uint16_t hC=TFT_WHITE,uint16_t borderColor=TFT_GREEN,uint16_t padColor=TFT_GREY);
    ~CLOCK1();

    void start(void);
    void render(void);
    void restart(void);

    void setColor(uint16_t sC,uint16_t mC,uint16_t hC,uint16_t bC,uint16_t pC);
};

#endif