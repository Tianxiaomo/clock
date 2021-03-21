#ifndef __AHT10_H_
#define __AHT10_H_

#include <Wire.h>

// uint8_t adress = 0x38; //设备地址 默认7位2进制数

class AHT10
{
private:
    /* data */
    TwoWire *wire;
    float T;
    float RH;
    int data[6];

public:
    AHT10(/* args */TwoWire &w);
    ~AHT10();

    void init();
    void update();
    float getTem();
    float getRh();
};

#endif