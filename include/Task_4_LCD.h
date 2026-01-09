#ifndef TASK_4_LCD_H
#define TASK_4_LCD_H

#include "Arduino.h"
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "0_glb.h"

#define I2C_ADDR_LCD 0x21 // I2C address of the LCD

void Task_4_LCD_Init();
void Task_4_LCD_Loop(void *pvParameters);

#endif // TASK_4_LCD_H