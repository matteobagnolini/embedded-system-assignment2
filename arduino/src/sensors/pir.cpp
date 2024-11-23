#include "hardware/pir.h"
#include <Arduino.h>

Pir::Pir(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Pir::calibrate() {
    delay(CALIBRATION_TIME_SEC*1000);   
}

bool Pir::isUserDetected() {
    int detected = digitalRead(pin);
    return detected == HIGH;
}
