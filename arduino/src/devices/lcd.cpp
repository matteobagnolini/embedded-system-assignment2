#include "hardware/lcd.h"
#include <Arduino.h>

LCD::LCD() : lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS) {
    lcd.init();
    lcd.backlight();
}

void LCD::display(char *msg) {
    lcd.clear();
    lcd.print(msg);
}

void LCD::clear() {
    lcd.clear();
}