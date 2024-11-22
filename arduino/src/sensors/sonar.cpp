#include "hardware/sonar.h"
#include <Arduino.h>

Sonar::Sonar(int triggPin, int echoPin) {
    this->triggPin = triggPin;
    this->echoPin = echoPin;
    pinMode(triggPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Sonar::getDistance() {
    digitalWrite(triggPin, LOW);
    delayMicroseconds(3);
    digitalWrite(triggPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggPin, LOW);

    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    return t * SPEED_OF_SOUND;
}
