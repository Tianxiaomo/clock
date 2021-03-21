#include "mpu.h"

MPU::MPU(/* args */ TwoWire &w) : mpu6050(w)
{
}

MPU::~MPU()
{
}

void MPU::init()
{
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
}

void MPU::update()
{
    mpu6050.update();
    // MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    //Serial.print(gx);
    //Serial.print(" ");
    //Serial.print(gy);
    //Serial.print(" ");
    //Serial.print(gz);
    //Serial.println(" ");

    // if (millis() - last_update_time > interval)
    // {
    //     if (ay > 3000 && flag)
    //     {
    //         encoder_diff--;
    //         flag = 0;
    //     }
    //     else if (ay < -3000 && flag)
    //     {
    //         encoder_diff++;
    //         flag = 0;
    //     }
    //     else
    //     {
    //         flag = 1;
    //     }

    //     if (ax > 10000)
    //     {
    //         encoder_state = LV_INDEV_STATE_PR;
    //     }
    //     else
    //     {
    //         encoder_state = LV_INDEV_STATE_REL;
    //     }

    //     last_update_time = millis();
    // }
}

float MPU::getTem()
{
    return mpu6050.getTemp();
}

float MPU::getAccelX()
{
    return mpu6050.getAccX();
}

float MPU::getAccelY()
{
    return mpu6050.getAccY();
}

float MPU::getAccelZ()
{
    return mpu6050.getAccZ();
}

float MPU::getGyroX()
{
    return mpu6050.getGyroX();
}

float MPU::getGyroY()
{
    return mpu6050.getGyroY();

    return gy;
}

float MPU::getGyroZ()
{
    return mpu6050.getGyroZ();
}
