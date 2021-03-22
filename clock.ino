#include <WiFi.h>
#include "clock1.h"
#include "mpu.h"
#include "aht10.h"
#include "log.h"
#include "clock2.h"
#include "ntp.h"

const char *ssid = "Meizu";
const char *password = "123456789@";

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
MPU *mpu;
AHT10 *aht;
UI *ui;
CLOCK1 *clock1 = new CLOCK1(tft);
CLOCK2 *clock2 = new CLOCK2(tft);

NTP *ntp = new NTP();

void taskMain(void *paramter);
void taskHumiture(void *paramter);

void setup()
{
    Serial.begin(115200);
    tft.init();
    Wire.begin();
    aht = new AHT10(Wire);

    // mpu = new MPU(Wire);
    // mpu->init();
    // aht->init();

    ui = clock2;
    ui->start();

    LOG("Connecting to %s \n", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    LOG(" CONNECTED\n");

    ntp->init();
    ntp->update();

    //disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    // xTaskCreatePinnedToCore
    xTaskCreate(
        taskMain,    /*任务函数*/
        "TaskClock", /*带任务名称的字符串*/
        100000,      /*堆栈大小，单位为字节*/
        NULL,        /*作为任务输入传递的参数*/
        1,           /*任务的优先级*/
        NULL);       /*任务句柄*/

    xTaskCreate(
        taskHumiture,   /*任务函数*/
        "TaskHumiture", /*带任务名称的字符串*/
        10000,          /*堆栈大小，单位为字节*/
        NULL,           /*作为任务输入传递的参数*/
        2,              /*任务的优先级*/
        NULL);          /*任务句柄*/
}

void loop()
{
    // mpu->update();
    // LOG("Temp %f , X %f , Y %f Z %f\n", mpu->getTem(),mpu->getAccelX(),mpu->getAccelY(),mpu->getAccelZ());
    // delay(1000);
    // ui->render();
    // aht->update();
    // LOG("T %f , RH %f\n", aht->getTem(), aht->getRh());
    delay(1000);
    ntp->update();
}

void taskMain(void *paramter)
{
    int i = 0;
    while (1)
    {
        LOG("taskMain\n");

        ui->render();
        vTaskDelay(1000);

        // ui->render();
        // // mpu.update(200);
        // if (i >= 10000)
        // {
        //     ui = clock1;
        //     if (ui == clock1)
        //     {
        //         ui == clock2;
        //     }
        //     else
        //     {
        //         ui == clock1;
        //     }
        //     i = 0;
        // }
        // i++;
        // vTaskDelay(20);
        // clock.updata();
    }
    // Serial.println(__FUNTION__);
    vTaskDelete(NULL);
}

void taskHumiture(void *paramter)
{
    while (1)
    {
        vTaskDelay(1000 * 60);
        LOG("T %f , RH %f\n", aht->getTem(), aht->getRh());
        aht->update();
    }
    // Serial.println(__FUNTION__);
    vTaskDelete(NULL);
}