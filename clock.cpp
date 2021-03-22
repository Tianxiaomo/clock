#include "clock.h"


CLOCK::CLOCK(/* args */)
{
}

CLOCK::~CLOCK()
{
}

void CLOCK::getTime()
{
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    hh = timeinfo.tm_hour;
    mm = timeinfo.tm_min;
    ss = timeinfo.tm_sec;
    md = timeinfo.tm_mday;
    wd = timeinfo.tm_wday;
    mon = timeinfo.tm_mon;
    year = timeinfo.tm_year;
    // Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
}
