#include "Task_1_DHT20.h"

float glb_temp = 0.0f; 
float glb_humid = 0.0f;

DHT20 sensor_dht20(&Wire); 


void Task_1_DHT20_Init() {
    sensor_dht20.begin();
}

void Task_1_DHT20_Loop(void *pvParameters) {
    float local_temp = 0.0f;
    float local_humid = 0.0f;
    Task_1_DHT20_Init();
    while(1){
        int err = sensor_dht20.read();
        if (err == DHT20_OK){
            local_temp = sensor_dht20.getTemperature();
            local_humid = sensor_dht20.getHumidity();
            glb_temp = local_temp;
            glb_humid = local_humid;
            // Serial.println("[DEBUG - DHT] DHT20 Temperature: " + String(local_temp) + " °C");
            // Serial.println("[DEBUG - DHT] DHT20 Humidity: " + String(local_humid) + " %");
        }
        else {
            // Serial.println("[DEBUG - DHT] DHT20 read error: " + String(err));
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}