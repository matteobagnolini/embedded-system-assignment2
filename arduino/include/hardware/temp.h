#pragma once

#include "devices/tempDetector.h"

class Temp: public TempDetector {
public:
    Temp(int pin, float maxTemp);
    bool isTempOk();
    float getTemperature();

private:
    int pin;
    float maxTemp;

};
