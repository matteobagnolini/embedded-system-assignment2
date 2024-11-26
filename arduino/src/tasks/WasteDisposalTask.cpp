#include <Arduino.h>
#include "tasks/wasteDisposalTask.h"
#include "globals.h"

WasteDisposalTask::WasteDisposalTask(
    int greenLedPin,
    int redLedPin,
    int openButtonPin,
    int closeButtonPin,
    int servoMotorPin
) {
    this->greenLedPin = greenLedPin;
    this->redLedPin = redLedPin;
    this->openButtonPin = openButtonPin;
    this->closeButtonPin = closeButtonPin;
    this->servoMotorPin = servoMotorPin;
}

void WasteDisposalTask::init(int period) {
    Task::init(period);
    greenLed = new Led(greenLedPin);
    redLed = new Led(redLedPin);
    openButton = new Button(openButtonPin);
    closeButton = new Button(closeButtonPin);
    servoDoor = new ServoMotor(servoMotorPin);
    state = AVAILABLE;
    servoDoor->close();     //check if this is ok
}

void WasteDisposalTask::tick() {
    currTime = millis();
    bool openButtonPressed = openButton->isPressed();
    bool closeButtonPressed = closeButton->isPressed();
    switch (state) {
        
        case AVAILABLE:
            greenLed->switchOn();
            if (openButtonPressed) {
                state = RECEIVING;
                servoDoor->open();
                timeInCurrState = 0;
            }
        
        case RECEIVING:
            timeInCurrState += currTime - lastTimeCheck;
            if ( isContainerFull ||
                 timeInCurrState >= MAX_TIME_TO_RECEIVE_WASTE_SEC*1000 ||
                 closeButtonPressed ) {
                state = RECEIVED;
                servoDoor->close();
                timeInCurrState = 0;
            }
        
        case RECEIVED:
            timeInCurrState += currTime - lastTimeCheck;
            if (isContainerFull) {
                state = CONTAINER_FULL;
                timeInCurrState = 0;
            }
            if (timeInCurrState >= TIME_BEFORE_BEING_AVAILABLE_AGAIN_SEC*1000) {
                state = AVAILABLE;
                timeInCurrState = 0;
            }
        
        case CONTAINER_FULL:
            greenLed->switchOff();
            redLed->switchOn();
            if (doEmptyContainer) {
                state = EMPTYING;
                servoDoor->openReverse();
                timeInCurrState = 0;
            }
        
        case EMPTYING:
            timeInCurrState += currTime - lastTimeCheck;
            if (timeInCurrState >= TIME_TO_EMPTY_CONTAINER_SEC*1000) {
                state = AVAILABLE;
                redLed->switchOff();
                greenLed->switchOn();
            }

    }
    lastTimeCheck = currTime;
}