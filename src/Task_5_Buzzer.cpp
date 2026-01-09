#include "Task_5_Buzzer.h"

#define BUZZER_PIN EXTERNAL_BUZZER_PIN



void Task_5_Buzzer_Init() {
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.println("[DEBUG - BUZZER] Buzzer Initialized");
}

void Task_5_Buzzer_Loop(void *pvParameters) {
    Task_5_Buzzer_Init();
    while(1){
        if (glb_alert == true) {
            for (int i = 0; i < 5; i++) {
                digitalWrite(BUZZER_PIN, HIGH);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                digitalWrite(BUZZER_PIN, LOW);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
            
        } else {
            digitalWrite(BUZZER_PIN, LOW);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}