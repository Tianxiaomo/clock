#ifndef __NTP_H_
#define __NTP_H_
#include "time.h"

class NTP
{
private:
    /* data */
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 3600 * 8;
    const int daylightOffset_sec = 0;

public:
    NTP(/* args */);
    ~NTP();
    void init();
    void update();
};

#endif