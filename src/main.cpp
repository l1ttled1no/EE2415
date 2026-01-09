#include <Arduino.h>
#include "0_glb.h"
#include "Task_1_DHT20.h"
#include "Task_2_Ultrasonic.h"
#include "Task_3_LED.h"
#include "Task_4_LCD.h"
#include "Task_5_Buzzer.h"
// put function declarations here:
void setup(){
  Serial.begin(115200);
  // for (auto i = 0; i < 10; i++) {
  //   Serial.println("Initializing... " + String(i));
  //   delay(1000);
  // }
  Wire.begin(11,12); 
  xTaskCreate(
    Task_1_DHT20_Loop,       // Function that implements the task.
    "DHT20 Task",            // Text name for the task.
    4096,                    // Stack size in words, not bytes.
    NULL,                    // Parameter passed into the task.
    1,                       // Priority at which the task is created.
    NULL);                   // Used to pass out the created task's handle.
  
  xTaskCreate(
    Task_2_Ultrasonic_Loop,       // Function that implements the task.
    "Ultrasonic Task",            // Text name for the task.
    4096,                    // Stack size in words, not bytes.
    NULL,                    // Parameter passed into the task.
    1,                       // Priority at which the task is created.
    NULL);                   // Used to pass out the created task's handle.

  xTaskCreate(
    Task_3_LED_Loop,       // Function that implements the task.
    "LED Task",            // Text name for the task.
    4096,                    // Stack size in words, not bytes.
    NULL,                    // Parameter passed into the task.
    1,                       // Priority at which the task is created.
    NULL);                   // Used to pass out the created task's handle.
  xTaskCreate(
    Task_4_LCD_Loop,       // Function that implements the task.
    "LCD Task",            // Text name for the task.
    8192,                    // Stack size in words, not bytes.
    NULL,                    // Parameter passed into the task.
    1,                       // Priority at which the task is created.
    NULL);                   // Used to pass out the created task's handle.

  xTaskCreate(
    Task_5_Buzzer_Loop,       // Function that implements the task.
    "Buzzer Task",            // Text name for the task.
    2048,                    // Stack size in words, not bytes.
    NULL,                    // Parameter passed into the task.
    1,                       // Priority at which the task is created.
    NULL);                   // Used to pass out the created task's handle.
}

void loop(){
  // Serial.println("Hello, World!");
  // vTaskDelay(1000 / portTICK_PERIOD_MS);
}