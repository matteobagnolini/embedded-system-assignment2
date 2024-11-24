#include "hardware/led.h"
#include <Arduino.h>

Led::Led(int pin) {
    this->pin = pin;
    this->isOn = false;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
    if (!isOn) {
        digitalWrite(pin, HIGH);
        isOn = true;
    }
}

void Led::switchOff() {
    if (isOn) {
        digitalWrite(pin, LOW);
        isOn = false;
    }
}
