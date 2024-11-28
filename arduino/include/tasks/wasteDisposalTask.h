#pragma once

#include "scheduler/task.h"
#include "hardware/led.h"
#include "hardware/button.h"
#include "hardware/servoMotor.h"

#define MAX_TIME_TO_RECEIVE_WASTE_SEC 60
#define TIME_BEFORE_BEING_AVAILABLE_AGAIN_SEC 10
#define TIME_TO_EMPTY_CONTAINER_SEC 10

class WasteDisposalTask : public Task {

public:
    WasteDisposalTask(int greenLedPin,
                      int redLedPin,
                      int openButtonPin,
                      int closeButtonPin,
                      int servoMotorPin
                      );
    void init(int period);
    void tick();

private:
    int greenLedPin;
    int redLedPin;
    int openButtonPin;
    int closeButtonPin;
    int servoMotorPin;
    Led *greenLed;
    Led *redLed;
    Button *openButton;
    Button *closeButton;
    ServoMotor *servoDoor;
    int lastTimeCheck;
    int timeInCurrState;
    
    enum { AVAILABLE,
           RECEIVING,
           RECEIVED,
           CONTAINER_FULL,
           EMPTYING
          } state;

};
