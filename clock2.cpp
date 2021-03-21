#include "clock2.h"

CLOCK2::CLOCK2(/* args */ TFT_eSPI &t) : UI(t)
{
}

CLOCK2::~CLOCK2()
{
}

void CLOCK2::start(void)
{
    //Serial.begin(115200);
    //   tft.init();
    //   tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}

void CLOCK2::render(void)
{
    // Adjust the time values by adding 1 second
    ss++; // Advance second
    if (ss == 60)
    {             // Check for roll-over
        ss = 0;   // Reset seconds to zero
        omm = mm; // Save last minute time for display update
        mm++;     // Advance minute
        if (mm > 59)
        { // Check for roll-over
            mm = 0;
            hh++; // Advance hour
            if (hh > 23)
            {           // Check for 24hr roll-over (could roll-over on 13)
                hh = 0; // 0 for 24 hour clock, set to 1 for 12 hour clock
            }
        }
    }

    // Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;

    if (omm != mm)
    { // Redraw hours and minutes time every minute
        omm = mm;
        // Draw hours and minutes
        if (hh < 10)
            xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
        xpos += tft.drawNumber(hh, xpos, ypos, 8);    // Draw hours
        xcolon = xpos;                                // Save colon coord for later to flash on/off later
        xpos += tft.drawChar(':', xpos, ypos - 8, 8);
        if (mm < 10)
            xpos += tft.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
        xpos += tft.drawNumber(mm, xpos, ypos, 8);    // Draw minutes
        xsecs = xpos;                                 // Sae seconds 'x' position for later display updates
    }
    if (oss != ss)
    { // Redraw seconds time every second
        oss = ss;
        xpos = xsecs;

        if (ss % 2)
        {                                               // Flash the colons on/off
            tft.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
            tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
            xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
            tft.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set colour back to yellow
        }
        else
        {
            tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
            xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        }

        //Draw seconds
        if (ss < 10)
            xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
        tft.drawNumber(ss, xpos, ysecs, 6);            // Draw seconds
    }
}

void CLOCK2::restart(void)
{

    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}