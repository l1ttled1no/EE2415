#include "Task_3_LED.h"

#define NEO_PIN EXTERNAL_NEOPIXEL_PIN

#define DEMACIA_3   10
#define DEMACIA_5   20
#define DEMACIA_7   30
#define DEMACIA_11  40

Adafruit_NeoPixel strip(4, NEO_PIN, NEO_GRB + NEO_KHZ800);

void Task_3_LED_Init() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Serial.println("[DEBUG - LED] NeoPixel Initialized");
}

void Task_3_LED_Loop(void *pvParameters) {
    Task_3_LED_Init();
    while(1){
        if (glb_alert){
            // Determine color based on motion count
            if (glb_motionCount >= DEMACIA_11) {
                strip.fill(strip.Color(255, 255, 255)); // White
            } else if (glb_motionCount >= DEMACIA_7) {
                strip.fill(strip.Color(0, 255, 0)); // Green
            } else if (glb_motionCount >= DEMACIA_5) {
                strip.fill(strip.Color(255, 255, 0)); // Yellow
            } else if (glb_motionCount >= DEMACIA_3) {
                strip.fill(strip.Color(0, 0, 255)); // Blue
            } else {
                strip.fill(strip.Color(255, 0, 0)); // Red
            }
            strip.show();
            
            // Keep LEDs on for 3 seconds
            vTaskDelay(500 / portTICK_PERIOD_MS);
            
            // Turn off LEDs
        }
        strip.fill(strip.Color(0, 0, 0));
        strip.show();
        glb_alert = false;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}