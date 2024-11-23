#include "hardware/servoMotor.h"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    motor.attach(pin);
}

void ServoMotor::open() {
    setPosition(OPEN);
}

void ServoMotor::close() {
    setPosition(CLOSE);
}

void ServoMotor::openReverse() {
    setPosition(REVERSE);
}

void ServoMotor::setPosition(int angle) {
    float coeff = (2250.0-750.0)/180;
    motor.write(750 + angle*coeff);
}