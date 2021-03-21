#include "clock1.h"
#include "mpu.h"
#include "aht10.h"
#include "log.h"

MPU *mpu;
AHT10 *aht;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
     aht = new AHT10(Wire);

    mpu = new MPU(Wire);

    mpu->init();
    // aht->init();
}

void loop()
{
    mpu->update();
    LOG("Temp %f , X %f , Y %f Z %f\n", mpu->getTem(),mpu->getAccelX(),mpu->getAccelY(),mpu->getAccelZ());
    delay(1000);

     aht->update();
     LOG("T %f , RH %f\n",aht->getTem(),aht->getRh());
     delay(1000);
}
