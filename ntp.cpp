#include "ntp.h"
#include <WiFi.h>
#include "time.h"

NTP::NTP(/* args */)
{
}

NTP::~NTP()
{
}

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %Y-%m-%d %H:%M:%S");
}

void NTP::init()
{
    //init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    // printLocalTime();
}

void NTP::update()
{
    printLocalTime();
}