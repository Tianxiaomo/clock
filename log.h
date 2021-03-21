#ifndef __LOG_H_
#define __LOG_H_

// #define LOG Serial.println
#define LOG(format, ...) printf(format, ##__VA_ARGS__)

#endif