#include "Task_2_Ultrasonic.h"

#define TRIGGER_PIN EXTERNAL_ULTSN_TRIGGER_PIN
#define ECHO_PIN EXTERNAL_ULTSN_ECHO_PIN
#define DETECTION_RANGE 100       // Detection range in cm
#define MIN_DISTANCE 2           // Minimum valid distance (cm)
#define MAX_TICK_COUNT 8        // Maximum tick count to count

int glb_motionCount = 0;
bool glb_alert = false;

float getDistance() {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
    if (duration == 0) {
        return -1;  // No echo received
    }
    
    float distance = duration * 0.034 / 2;  // Convert to cm
    return distance;
}

void Task_2_Ultrasonic_Init() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.println("[DEBUG - ULTRASONIC] Initialized");
    
}

void Task_2_Ultrasonic_Loop(void *pvParameters) {
    Task_2_Ultrasonic_Init();
    bool isAdded = false; 
    uint8_t tick_count = 0; 
    while(1) {
        float distance = getDistance();
        // Check if person is in detection range
        bool inRange = (distance > MIN_DISTANCE && distance < DETECTION_RANGE);
        // Serial.println("[DEBUG - ULTRASONIC] Distance: " + String(distance) + " cm");
        // Serial.println("[DEBUG - ULTRASONIC] In range: " + String(inRange));
        if (inRange) {
            tick_count++; 
            if (tick_count >= MAX_TICK_COUNT && !isAdded) {
                isAdded = true;
                glb_alert = true;
                glb_motionCount++;
                Serial.println("[DEBUG - ULTRASONIC] Person detected. Person count: " + String(glb_motionCount));
            }
        } else {
            tick_count = 0;
            isAdded = false;
            glb_alert = false;
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);  // Check every 50ms
    }
}