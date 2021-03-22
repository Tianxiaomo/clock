#ifndef __UI_H_
#define __UI_H_

#include <TFT_eSPI.h> // Hardware-specific library

#define TFT_GREY 0x5AEB

class UI
{
protected:
    /* data */
    TFT_eSPI tft;       // Invoke custom library
    uint16_t blackColor;
    uint16_t color;

public:
    UI(/* args */TFT_eSPI &t);

    virtual void start(void) = 0;
    virtual void render(void) = 0;
    virtual void restart(void) = 0;
};




#endif