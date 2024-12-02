#pragma once

class UserDetector {

public:
    virtual void calibrate() = 0;
    virtual bool isUserDetected() = 0;

};
