#include "tasks/userDetectTask.h"
#include <Arduino.h>
#include "globals.h"

UserDetectTask::UserDetectTask(int pin) {
    this->pir = new Pir(pin);
}

void UserDetectTask::init(int period) {
    Task::init(period);
    pir->calibrate();
    this->timeElapsedNoDetection = 0;
    state = SLEEP;
    sleepMode = true;
}

void UserDetectTask::tick() {
    int currTime = millis();
    bool detected = pir->isUserDetected();
    switch (state) {

        case SLEEP:
            if (detected) {
                timeElapsedNoDetection = 0;
                state = READY;
                sleepMode = false;
            }
            break;
        
        case READY:
            if (!detected) {
                timeElapsedNoDetection += currTime - lastTimeCheck;
            } else {
                timeElapsedNoDetection = 0;
            }
            if (timeElapsedNoDetection >= TIME_BEFORE_SLEEP_SEC*1000) {
                state = SLEEP;
                sleepMode = true;
            }
            break;

    }
    lastTimeCheck = currTime;
}
