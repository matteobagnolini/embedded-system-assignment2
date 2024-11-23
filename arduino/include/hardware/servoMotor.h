#pragma once

#include "devices/door.h"
#include "ServoTimer2.h"

#define OPEN 180
#define CLOSE 90
#define REVERSE 0

class ServoMotor : public Door {

public:
    ServoMotor(int pin);
    void open();
    void close();
    void openReverse();

private:
    int pin;
    ServoTimer2 motor;
    void setPosition(int angle);

};
