#pragma once

#include "devices/wasteDetector.h"

#define SPEED_OF_SOUND 343.4

class Sonar : public WasteDetector {

public:
    Sonar(int triggPin, int echoPin);
    float getDistance();

private:
    int triggPin;
    int echoPin;

};
