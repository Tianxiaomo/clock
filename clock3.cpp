#include "clock3.h"


CLOCK3::CLOCK3(/* args */ TFT_eSPI &t, uint8_t ox, uint8_t oy, uint8_t x, uint8_t y) : UI(t), osx(ox), osy(oy), gx(x), gy(y)
{
}

CLOCK3::~CLOCK3()
{
}

void CLOCK3::start(void)
{
    tft.fillScreen(TFT_WHITE);

    // tft.setTextColor(color); // Adding a background colour erases previous text automatically
    getTime();
    h1 = hh / 10;
    h2 = hh % 10;
    m1 = mm / 10;
    m2 = mm % 10;
    s1 = ss / 10;
    s2 = ss % 10;
    
    printf("%d %d %d %d %d %d\n",h1,h2,m1,m2,s1,s2);

    tft.pushImage(osx, osy, gWidth, gHeight, gImage_v[h1 * 5 + 1]);
    tft.pushImage(osx + gWidth + gx, osy, gWidth, gHeight, gImage_v[h2 * 5 + 1]);
    tft.pushImage(osx, osy + gHeight + gy, gWidth, gHeight, gImage_v[m1 * 5 + 1]);
    tft.pushImage(osx + gWidth + gx, osy + gHeight + gy, gWidth, gHeight, gImage_v[m2 * 5 + 1]);

    tft.pushImage(osx + (gWidth + gx) * 2, osy, gWidth, gHeight, gImage_v[s1 * 5 + 1]);
    tft.pushImage(osx + (gWidth + gx) * 2, osy + gHeight + gy, gWidth, gHeight, gImage_v[s2 * 5 + 1]);

    count = 0;
}

void CLOCK3::render(void)
{
    getTime();
    if (ss == lastSs && count == 5)
        return;
    if (ss != lastSs) count = 0;
    lastSs = ss;

    s1 = ss / 10;
    s2 = ss % 10;
    tft.pushImage(osx + (gWidth + gx) * 2, osy + gHeight + gy, gWidth, gHeight, gImage_v[(s2 * 5 + 1 + count) % 50]);

    if (s2 == 9){
        tft.pushImage(osx + (gWidth + gx) * 2, osy, gWidth, gHeight, gImage_v[(s1 * 5 + 1 + count) % 50]);
    }
    count++;
}

void CLOCK3::restart(void)
{
    tft.setRotation(0);
}