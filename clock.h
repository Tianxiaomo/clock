#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <Arduino.h>
#include "time.h"

// struct tm {
//         int8_t          tm_sec; /**< seconds after the minute - [ 0 to 59 ] */
//         int8_t          tm_min; /**< minutes after the hour - [ 0 to 59 ] */
//         int8_t          tm_hour; /**< hours since midnight - [ 0 to 23 ] */
//         int8_t          tm_mday; /**< day of the month - [ 1 to 31 ] */
//         int8_t          tm_wday; /**< days since Sunday - [ 0 to 6 ] */
//         int8_t          tm_mon; /**< months since January - [ 0 to 11 ] */
//         int16_t         tm_year; /**< years since 1900 */
//         int16_t         tm_yday; /**< days since January 1 - [ 0 to 365 ] */
//         int16_t         tm_isdst; /**< Daylight Saving Time flag */
// }
class CLOCK
{
private:
    struct tm timeinfo;

protected:
    /* data */
    int8_t hh, mm, ss, md, wd, mon, year; // Get H, M, S from compile time
    int8_t lastSs = 0;
public:
    CLOCK(/* args */);
    ~CLOCK();

    void getTime();
};

#endif