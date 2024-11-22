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
            Serial.println("Normal Temp");
            if (!temp->isTempOk()) {
                state = HIGH_TEMP;
                timeOnHighTemp = 0;
                Serial.println("Switching to high temp");
            }
            break;
        
        case HIGH_TEMP:
            Serial.print("High Temp for ");
            Serial.print((float)timeOnHighTemp/1000);
            Serial.print(" seconds\n");

            if (temp->isTempOk()) {
                state = NORMAL_TEMP;
            } else {
                timeOnHighTemp += currTime - lastTimeCheck;
            }
            if (timeOnHighTemp >= MAX_TIME_ON_HIGH_TEMP*1000) {
                state = PROBLEM_DETECTED;
                Serial.println("Switching to problem detected");
            }
            break;
        
        case PROBLEM_DETECTED:
        Serial.println("Problem Detected");
            // Problem detected
            break;

    }
    lastTimeCheck = currTime;
}
