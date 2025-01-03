#include "tasks/wasteDetectTask.h"
#include <Arduino.h>
#include "globals.h"

WasteDetectTask::WasteDetectTask(int triggPin, int echoPin) {
    this->sonar = new Sonar(triggPin, echoPin);
}

void WasteDetectTask::init(int period) {
    Task::init(period);
    this->state = EMPTY;
    isContainerFull = false;
}

void WasteDetectTask::tick() {
    float dist = sonar->getDistance();
    fillingPercentage = 100*(dist - EMPTY_DISTANCE) / (THRESHOLD_DISTANCE - EMPTY_DISTANCE);
    switch (state) {

        case EMPTY:
            isContainerFull = false;
            if (dist <= EMPTY_DISTANCE && dist >= THRESHOLD_DISTANCE) {
                state = PARTIAL;
            } else if (dist <= THRESHOLD_DISTANCE) {
                state = FULL;
                isContainerFull = true;
            }
        break;
    
    case PARTIAL:
        if (dist >= EMPTY_DISTANCE) {
            state = EMPTY;
        } else if (dist <= THRESHOLD_DISTANCE) {
            state = FULL;
            isContainerFull = true;
        }
        break;

    case FULL:
        if (dist > THRESHOLD_DISTANCE) {
            state = PARTIAL;
            isContainerFull = false;
        }
        break;

    }
}
