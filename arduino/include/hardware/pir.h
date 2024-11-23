#pragma once

#include "sensors/userDetector.h"

#define CALIBRATION_TIME_SEC 30

class Pir : public UserDetector {

public:
    Pir(int pin);
    void calibrate();
    bool isUserDetected();

private:
    int pin;

};
