#include "hardware/temp.h"
#include <Arduino.h>

Temp::Temp(int pin, float maxTemp) {
    this->pin = pin;
    this->maxTemp = maxTemp;
    pinMode(pin, INPUT);
}

bool Temp::isTempOk() {
    return getTemperature() < this->maxTemp;
}

float Temp::getTemperature() {
    int reading = analogRead(this->pin);
    float voltage = ((float)reading * 5) / 1024.0;
    float tempC = (voltage - 0.5) * 100;
    return tempC;
}