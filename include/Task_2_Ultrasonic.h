#ifndef TASK_2_ULTRASONIC_H
#define TASK_2_ULTRASONIC_H

#include "Arduino.h"
#include <Wire.h>
#include "0_glb.h"

void Task_2_Ultrasonic_Init();
void Task_2_Ultrasonic_Loop(void *pvParameters);

#endif // TASK_2_ULTRASONIC_H