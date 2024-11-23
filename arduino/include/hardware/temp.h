#pragma once

#include "devices/tempDetector.h"

class Temp: public TempDetector {
public:
    Temp(int pin, float maxTemp);
    bool isTempOk();

private:
    int pin;
    float maxTemp;
    float getTemperature();

};
