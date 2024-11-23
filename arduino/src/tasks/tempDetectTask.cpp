#include "tasks/tempDetectTask.h"
#include <Arduino.h>

TempDetectTask::TempDetectTask(int pin) {
    this->temp = new Temp(pin, MAX_TEMP);
}

void TempDetectTask::init(int period) {
    Task::init(period);
    this->timeOnHighTemp = 0;
    this->lastTimeCheck = millis();
    this->state = NORMAL_TEMP;
}

void TempDetectTask::tick() {
    long currTime = millis();
    switch (state) {

        case NORMAL_TEMP:
            if (!temp->isTempOk()) {
                state = HIGH_TEMP;
                timeOnHighTemp = 0;
            }
            break;
        
        case HIGH_TEMP:
            if (temp->isTempOk()) {
                state = NORMAL_TEMP;
            } else {
                timeOnHighTemp += currTime - lastTimeCheck;
            }
            if (timeOnHighTemp >= MAX_TIME_ON_HIGH_TEMP*1000) {
                state = PROBLEM_DETECTED;
            }
            break;
        
        case PROBLEM_DETECTED:
            // Problem detected
            break;

    }
    lastTimeCheck = currTime;
}
