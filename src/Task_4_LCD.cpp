#include "Task_4_LCD.h"

LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 16, 2); 

void Task_4_LCD_Init() {
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LCD Initialized");
    Serial.println("[DEBUG - LCD] LCD Initialized");
}

void Task_4_LCD_Loop(void *pvParameters) {
    Task_4_LCD_Init();
    while(1){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ppl Count: " + String(glb_motionCount)); 
        lcd.setCursor(0, 1);
        lcd.print("T:" + String(glb_temp, 1) + "oC"+ " H:" + String(glb_humid, 1) + "%");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}