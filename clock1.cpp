#include "clock1.h"

boolean initial = 1;

// CLOCK1::CLOCK1(/* args */ TFT_eSPI &t) : UI(t)
// {
// }

CLOCK1::CLOCK1(/* args */ TFT_eSPI &t, uint16_t sC, uint16_t mC, uint16_t hC, uint16_t bC, uint16_t pC) : UI(t), sColor(sC), mColor(mC), hColor(hC), borderColor(bC), padColor(pC)
{
}

CLOCK1::~CLOCK1()
{
}

void CLOCK1::setColor(uint16_t sC,uint16_t mC,uint16_t hC,uint16_t bC,uint16_t pC)
{
    sColor = sC;
    mColor = mC;
    hColor = hC;
    borderColor = bC;
    padColor = pC;
}

void CLOCK1::start(void)
{
    tft.setRotation(0);

    //tft.fillScreen(TFT_BLACK);
    //tft.fillScreen(TFT_RED);
    //tft.fillScreen(TFT_GREEN);
    //tft.fillScreen(TFT_BLUE);
    //tft.fillScreen(TFT_BLACK);
    tft.fillScreen(blackColor);

    tft.setTextColor(color); // Adding a background colour erases previous text automatically

    // Draw clock face
    tft.fillCircle(120, 120, 118, borderColor);
    tft.fillCircle(120, 120, 110, padColor);

    // Draw 12 lines
    for (int i = 0; i < 360; i += 30)
    {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 114 + 120;
        yy0 = sy * 114 + 120;
        x1 = sx * 100 + 120;
        yy1 = sy * 100 + 120;

        tft.drawLine(x0, yy0, x1, yy1, borderColor);
    }

    // Draw 60 dots
    for (int i = 0; i < 360; i += 6)
    {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 102 + 120;
        yy0 = sy * 102 + 120;
        // Draw minute markers
        tft.drawPixel(x0, yy0, sColor);

        // Draw main quadrant dots
        if (i == 0 || i == 180)
            tft.fillCircle(x0, yy0, 2, sColor);
        if (i == 90 || i == 270)
            tft.fillCircle(x0, yy0, 2, sColor);
    }

    tft.fillCircle(120, 121, 3, sColor);

    // Draw text at position 120,260 using fonts 4
    // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
    // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .
    tft.drawCentreString("Time flies", 120, 120, 4);

    // targetTime = millis() + 1000;
}

void CLOCK1::render(void)
{
    getTime();
    if (ss == lastSs)
        return;
    lastSs = ss;

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss * 6;                     // 0-59 -> 0-354
    mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
    hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg - 90) * 0.0174532925);
    hy = sin((hdeg - 90) * 0.0174532925);
    mx = cos((mdeg - 90) * 0.0174532925);
    my = sin((mdeg - 90) * 0.0174532925);
    sx = cos((sdeg - 90) * 0.0174532925);
    sy = sin((sdeg - 90) * 0.0174532925);

    if (ss == 0 || initial)
    {
        initial = 0;
        // Erase hour and minute hand positions every minute
        tft.drawLine(ohx, ohy, 120, 121, padColor);
        ohx = hx * 62 + 121;
        ohy = hy * 62 + 121;
        tft.drawLine(omx, omy, 120, 121, padColor);
        omx = mx * 84 + 120;
        omy = my * 84 + 121;
    }

    // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
    tft.drawLine(osx, osy, 120, 121, padColor);
    osx = sx * 90 + 121;
    osy = sy * 90 + 121;
    tft.drawLine(osx, osy, 120, 121, sColor);
    tft.drawLine(ohx, ohy, 120, 121, hColor);
    tft.drawLine(omx, omy, 120, 121, mColor);
    tft.drawLine(osx, osy, 120, 121, sColor);

    tft.fillCircle(120, 121, 3, sColor);
}

void CLOCK1::restart(void)
{
    tft.setRotation(0);

    //tft.fillScreen(TFT_BLACK);
    //tft.fillScreen(TFT_RED);
    //tft.fillScreen(TFT_GREEN);
    //tft.fillScreen(TFT_BLUE);
    //tft.fillScreen(TFT_BLACK);
    tft.fillScreen(TFT_GREY);

    tft.setTextColor(TFT_WHITE, TFT_GREY); // Adding a background colour erases previous text automatically

    // Draw clock face
    tft.fillCircle(120, 120, 118, TFT_GREEN);
    tft.fillCircle(120, 120, 110, TFT_BLACK);

    // Draw 12 lines
    for (int i = 0; i < 360; i += 30)
    {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 114 + 120;
        yy0 = sy * 114 + 120;
        x1 = sx * 100 + 120;
        yy1 = sy * 100 + 120;

        tft.drawLine(x0, yy0, x1, yy1, TFT_GREEN);
    }

    // Draw 60 dots
    for (int i = 0; i < 360; i += 6)
    {
        sx = cos((i - 90) * 0.0174532925);
        sy = sin((i - 90) * 0.0174532925);
        x0 = sx * 102 + 120;
        yy0 = sy * 102 + 120;
        // Draw minute markers
        tft.drawPixel(x0, yy0, TFT_WHITE);

        // Draw main quadrant dots
        if (i == 0 || i == 180)
            tft.fillCircle(x0, yy0, 2, TFT_WHITE);
        if (i == 90 || i == 270)
            tft.fillCircle(x0, yy0, 2, TFT_WHITE);
    }

    tft.fillCircle(120, 121, 3, TFT_WHITE);

    // Draw text at position 120,260 using fonts 4
    // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
    // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .
    tft.drawCentreString("Time flies", 120, 120, 4);
}