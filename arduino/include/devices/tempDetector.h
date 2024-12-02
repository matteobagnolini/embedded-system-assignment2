#pragma once

class TempDetector {

public:
    virtual bool isTempOk() = 0;
    virtual float getTemperature() = 0;

};
