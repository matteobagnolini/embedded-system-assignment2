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
    long currTime = millis();
    bool openButtonPressed = openButton->isPressed();
    bool closeButtonPressed = closeButton->isPressed();
    switch (state) {
        
        case AVAILABLE:
            Serial.println("WST: AVAILABLE");
            greenLed->switchOn();
            lcd->display("PRESS OPEN TO ENTER WASTE");
            if (openButtonPressed) {
                state = RECEIVING;
                servoDoor->open();
                timeInCurrState = 0;
                lcd->clear();
            }
            break;
        
        case RECEIVING:            
            Serial.println("WST: RECEIVING");
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("PRESS CLOSE WHEN DONE");
            if ( isContainerFull ||
                 timeInCurrState >= MAX_TIME_TO_RECEIVE_WASTE_SEC*1000 ||
                 closeButtonPressed ) {
                state = RECEIVED;
                servoDoor->close();
                timeInCurrState = 0;
                lcd->clear();
            }
            break;
        
        case RECEIVED:
            Serial.println("WST: RECEIVED");
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("WASTE RECEIVED");
            if (isContainerFull) {
                state = CONTAINER_FULL;
                timeInCurrState = 0;
            }
            if (timeInCurrState >= TIME_BEFORE_BEING_AVAILABLE_AGAIN_SEC*1000) {
                state = AVAILABLE;
                timeInCurrState = 0;
                lcd->clear();
            }
            break;
        
        case CONTAINER_FULL:
            Serial.println("WST: FULL");
            greenLed->switchOff();
            redLed->switchOn();
            lcd->display("CONTAINER FULL");
            if (doEmptyContainer) {
                state = EMPTYING;
                servoDoor->openReverse();
                timeInCurrState = 0;
                lcd->clear();
            }
            break;
        
        case EMPTYING:
            Serial.println("WST: EMPTYING");
            timeInCurrState += currTime - lastTimeCheck;
            lcd->display("EMPTYING THE CONTAINER..");
            if (timeInCurrState >= TIME_TO_EMPTY_CONTAINER_SEC*1000) {
                state = AVAILABLE;
                doEmptyContainer = false;
                redLed->switchOff();
                greenLed->switchOn();
                lcd->clear();
            }
            break;

    }
    lastTimeCheck = currTime;
}