#include "hardware/lcd.h"
#include <Arduino.h>

LCD::LCD() : lcd(0x27, 20, 4) {
    Serial.println("Inside lcd init");  
    lcd.init();
    lcd.backlight();
    Serial.println("Init lcd");
}

void LCD::display(char *msg) {
    lcd.clear();
    lcd.print(msg);
}

void LCD::clear() {
    lcd.clear();
}
