#include <WiFi.h>
#include "clock1.h"
#include "mpu.h"
#include "aht10.h"
#include "log.h"
#include "clock2.h"
#include "ntp.h"
#include "cellularAutomata.h"
#include "clock3.h"

const char *ssid = "Meizu";
const char *password = "123456789@";

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

MPU *mpu;
AHT10 *aht;
UI *ui;
CLOCK1 *clock1 = new CLOCK1(tft);
CLOCK2 *clock2 = new CLOCK2(tft);
CLOCK3 *clock3 = new CLOCK3(tft, 6, 10, 6, 10);

NTP *ntp = new NTP();
AUTOMATA *cell = new AUTOMATA(tft);

void taskMain(void *paramter);
void taskHumiture(void *paramter);

// void fun1(char *string)
// {
//     printf("%d %d %d\n", string[0], string[1], strlen(string));
// }

// void drawHanzi(int32_t x, int32_t y, const char c[3], uint32_t color)
// { //显示单一汉字

//     for (int k = 0; k < 5; k++)
//         if (hanzi16[k].Index[0] == c[0] && hanzi16[k].Index[1] == c[1] && hanzi16[k].Index[2] == c[2])
//         {
//             tft.drawBitmap(x, y, hanzi16[k].hz16_Id, hanzi16[k].hz_width, 16, color);
//         }
// }
// void drawHanziS(int32_t x, int32_t y, const char str[], uint32_t color)
// { //显示整句汉字，字库目前有限，比较简单，没有换行功能，上下输出，左右输出是在函数内实现
//     int y0 = y;
//     for (int i = 0; i < strlen(str); i += 3)
//     {
//         drawHanzi(x, y0, str + i, color);
//         y0 += 20;
//     }
// }

void drawString(char *string, uint8_t x, uint8_t y, uint32_t color)
{
    for (int i = 0; i < strlen(string); i += 2)
    {
        uint16_t t = string[i];
        uint32_t index1 = (t * 256) + string[i + 1];
        printf("drawString %d \n", index1);
        index1 = index1 * 32;
        printf("drawString %d \n", index1);

        tft.drawBitmap(x, y, (const uint8_t *)DzkCode[index1], 16, 16, color);
    }
}

void setup()
{
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    // fun1("我");
    drawString("我爱你中国", 10, 50, TFT_RED);
    pinMode(0, INPUT_PULLUP);

    Wire.begin();
    aht = new AHT10(Wire);
    aht->init();
    aht->update();
    LOG("aht inited\n");

    // mpu = new MPU(Wire);
    // mpu->init();

    LOG("Connecting to %s \n", ssid);
    tft.drawCentreString("Wifi Connectting...", 120, 120, 4);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    LOG(" CONNECTED\n");

    ntp->init();
    ntp->update();

    ui = clock3;
    ui->start();

    // LOG("tft inited %d\n",DzkCode[int(aht->getTem())]);

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
        if (ui == cell)
        {
            vTaskDelay(100);
        }
        else
        {
            vTaskDelay(100);
        }
    }
    vTaskDelete(NULL);
}

void taskHumiture(void *paramter)
{
    int i = 0;
    while (1)
    {
        // vTaskDelay(1000 * 60);
        vTaskDelay(100);
        LOG("T %f , RH %f\n", aht->getTem(), aht->getRh());
        if (digitalRead(0) == 0)
        {
            switch (i)
            {
            case /* constant-expression */ 0:
                /* code */
                ui = clock2;
                ui->start();
                ui->render();
                break;
            case 1:
                ui = cell;
                ui->start();
                ui->render();
                break;
            case 2:
                ui = clock1;
                ui->start();
                ui->render();
            default:
                break;
            }
            i++;
            if (i > 2)
                i = 0;
        }
        aht->update();
    }
    // Serial.println(__FUNTION__);
    vTaskDelete(NULL);
}