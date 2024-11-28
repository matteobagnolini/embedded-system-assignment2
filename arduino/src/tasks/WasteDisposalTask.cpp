#include <Arduino.h>
#include "tasks/wasteDisposalTask.h"
#include "hardware/lcd.h"
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
    timeInCurrState = 0;
    lastTimeCheck = 0;
}

void WasteDisposalTask::init(int period) {
    Task::init(period);
    greenLed = new Led(greenLedPin);
    redLed = new Led(redLedPin);
    openButton = new Button(openButtonPin);
    closeButton = new Button(closeButtonPin);
    servoDoor = new ServoMotor(servoMotorPin);
    lcd = new LCD();
    state = AVAILABLE;
    servoDoor->close();
    lcd->display("Init completed..");
    Serial.println("Init completed");
}

void WasteDisposalTask::tick() {
    unsigned long currTime = millis();
    bool openButtonPressed = openButton->isPressed();
    bool closeButtonPressed = closeButton->isPressed();
    switch (state) {
        
        case AVAILABLE:
            greenLed->switchOn();
            lcd->display("PRESS OPEN TO ENTER WASTE");
            if (isContainerFull) {
                state = CONTAINER_FULL;
                servoDoor->close();
                timeInCurrState = 0;
            }
            if (openButtonPressed) {
                state = RECEIVING;
                servoDoor->open();
                timeInCurrState = 0;
            }
            if (tempProblemDetected) {
                state = PROBLEM_DETECTED;
            }
            break;
        
        case RECEIVING:            
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("PRESS CLOSE WHEN DONE");
            if ( isContainerFull ||
                 timeInCurrState >= MAX_TIME_TO_RECEIVE_WASTE_SEC*1000 ||
                 closeButtonPressed ) {
                state = RECEIVED;
                servoDoor->close();
                timeInCurrState = 0;
            }
            if (tempProblemDetected) {
                servoDoor->close();
                state = PROBLEM_DETECTED;
            }
            break;
        
        case RECEIVED:
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("WASTE RECEIVED");
            if (isContainerFull) {
                state = CONTAINER_FULL;
                timeInCurrState = 0;
            }
            if (timeInCurrState >= TIME_BEFORE_BEING_AVAILABLE_AGAIN_SEC*1000) {
                state = AVAILABLE;
                timeInCurrState = 0;
            }
            break;
        
        case CONTAINER_FULL:
            greenLed->switchOff();
            redLed->switchOn();
            lcd->display("CONTAINER FULL");
            if (doEmptyContainer) {
                state = EMPTYING;
                servoDoor->openReverse();
                timeInCurrState = 0;
            }
            if (tempProblemDetected) {
                state = PROBLEM_DETECTED;
            }
            break;
        
        case EMPTYING:
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("EMPTYING THE CONTAINER..");
            if (timeInCurrState >= TIME_TO_EMPTY_CONTAINER_SEC*1000) {
                state = AVAILABLE;
                redLed->switchOff();
                greenLed->switchOn();
            }
            break;

        case PROBLEM_DETECTED:
            lcd->display("PROBLEM DETECTED");
            greenLed->switchOff();
            redLed->switchOn();
            if (!tempProblemDetected) {
                if (isContainerFull)
                    state = CONTAINER_FULL;
                else
                    state = AVAILABLE;
            }

    }
    lastTimeCheck = currTime;
}