#pragma once

#include "scheduler/task.h"
#include "hardware/led.h"
#include "hardware/button.h"
#include "hardware/servoMotor.h"
#include "hardware/lcd.h"

#define MAX_TIME_TO_RECEIVE_WASTE_SEC 30
#define TIME_BEFORE_BEING_AVAILABLE_AGAIN_SEC 3
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
    LCD *lcd;

    unsigned long lastTimeCheck;
    unsigned long timeInCurrState;
    
    enum State { AVAILABLE,
           RECEIVING,
           RECEIVED,
           CONTAINER_FULL,
           EMPTYING,
           PROBLEM_DETECTED,
           SLEEP
          } state;

};
