#ifndef TASK_1_DHT20_H
#define TASK_1_DHT20_H
#include "Arduino.h"
#include "DHT20.h"
#include <Wire.h>
#include "0_glb.h"

void Task_1_DHT20_Init();
void Task_1_DHT20_Loop(void *pvParameters);

#endif // TASK_1_DHT20_H

