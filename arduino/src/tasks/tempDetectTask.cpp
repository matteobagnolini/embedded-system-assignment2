#include "tasks/tempDetectTask.h"
#include <Arduino.h>

TempDetectTask::TempDetectTask(int pin) {
    this->temp = new Temp(pin, MAX_TEMP);
}

void TempDetectTask::init(int period) {
    Task::init(period);
    this->timeOnHighTemp = 0;
    this->lastTimeCheck = millis();     // can we delete this? We dont need lastTimeCheck in first state
    this->state = NORMAL_TEMP;
}

void TempDetectTask::tick() {
    long currTime = millis();
    bool tempOk = temp->isTempOk();
    switch (state) {

        case NORMAL_TEMP:
            if (!tempOk) {
                state = HIGH_TEMP;
                timeOnHighTemp = 0;
            }
            break;
        
        case HIGH_TEMP:
            if (tempOk) {
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
