#pragma once

#include "devices/userLCD.h"
#include <LiquidCrystal_I2C.h>

#define LCD_I2C_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

class LCD : public UserLCD {

public:
    LCD();
    void display(char *msg);
    void clear();

private:
    LiquidCrystal_I2C lcd;

};

extern LCD lcd;