#pragma once

#include "devices/userDetector.h"

#define CALIBRATION_TIME_SEC 1

class Pir : public UserDetector {

public:
    Pir(int pin);
    void calibrate();
    bool isUserDetected();

private:
    int pin;

};
