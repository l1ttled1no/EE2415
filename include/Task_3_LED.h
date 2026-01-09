
#ifndef TASK_3_LED_H
#define TASK_3_LED_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "0_glb.h"

void Task_3_LED_Init();
void Task_3_LED_Loop(void *pvParameters);

#endif // TASK_3_LED_H