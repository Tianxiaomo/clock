#include "clock1.h"
#include "mpu.h"
#include "aht10.h"
#include "log.h"
#include "clock2.h"


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

MPU *mpu;
AHT10 *aht;
UI *ui;
CLOCK1 *clock1;
CLOCK2 *clock2;

void setup()
{
    Serial.begin(115200);
    tft.init();

    Wire.begin();
    aht = new AHT10(Wire);

    // mpu = new MPU(Wire);
    // mpu->init();
    // aht->init();

    clock1 = new CLOCK1(tft);
    clock2 = new CLOCK2(tft);
    ui = clock2;

    ui->start();
}

void loop()
{
    // mpu->update();
    // LOG("Temp %f , X %f , Y %f Z %f\n", mpu->getTem(),mpu->getAccelX(),mpu->getAccelY(),mpu->getAccelZ());
    // delay(1000);
    ui->render();
    aht->update();
    LOG("T %f , RH %f\n", aht->getTem(), aht->getRh());
    delay(1000);
}
