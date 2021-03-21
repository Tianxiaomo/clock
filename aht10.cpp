#include "aht10.h"

AHT10::AHT10(/* args */TwoWire &w):wire(&w)
{
}

AHT10::~AHT10()
{
}

void AHT10::init()
{
    // wire->begin();
    // Serial.begin(9600);
}

void AHT10::update()
{
    wire->beginTransmission(0x38);
    wire->requestFrom(0x38, 6);

    while (wire->available())
    {
        for (int i = 0; i < 6; i++)
        {
            data[i] = wire->read();
            // Serial.println(data[i]);
        }

        if (data[0] & 0x08 == 0)
        {
            // Serial.println("进行初始化");
            // Serial.println(wire->read());
            wire->write(0xE1);
            wire->write(0x08);
            wire->write(0x00);
        }
        else
        {
            // Serial.println("不需要初始化");
            // Serial.println(wire->read());
            wire->write(0xAC);
            wire->write(0x33);
            wire->write(0x00);
            delayMicroseconds(75);

            if (data[0] & 0x80 == 0)
            {
                // Serial.println("需要等待完成");
                // Serial.println(wire->read());
            }
            else
            {
                // Serial.println("不需要等待");
                // Serial.println(wire->read());
            }
        }
    }
    wire->endTransmission();
    RH = ((data[1] << 12) | (data[2] << 4)) | (data[3] >> 4);
    T = ((data[3] & 0x0f) << 16) | (data[4] << 8) | data[5];
    RH = (RH / pow(2, 20)) * 100;
    T = (T / pow(2, 20)) * 200 - 50;

    // Serial.print("湿度为");
    // Serial.println(RH);
    // Serial.print("温度为");
    // Serial.println(T);
}

float AHT10::getTem()
{
    return T;
}

float AHT10::getRh()
{
    return RH;
}