#include "tasks/tempDetectTask.h"
#include <Arduino.h>
#include "globals.h"

#include "communications/MsgService.h"

TempDetectTask::TempDetectTask(int pin) {
    this->temp = new Temp(pin, MAX_TEMP);
}

void TempDetectTask::init(int period) {
    Task::init(period);
    this->timeOnHighTemp = 0;
    this->state = NORMAL_TEMP;
    tempProblemDetected = false;
}

void TempDetectTask::tick() {
    long currTime = millis();
    temperature = temp->getTemperature();
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
                tempProblemDetected = true;
            }
            break;
        
        case PROBLEM_DETECTED:
            if (!tempProblemDetected) {
                state = NORMAL_TEMP;
            }
            break;

    }
    lastTimeCheck = currTime;
}
