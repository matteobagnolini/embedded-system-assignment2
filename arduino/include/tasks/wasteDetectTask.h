#pragma once

#include "hardware/sonar.h"
#include "scheduler/task.h"

#define THRESHOLD_DISTANCE 0.10     // meters
#define EMPTY_DISTANCE 0.50

class WasteDetectTask : public Task {

public:
    WasteDetectTask(int triggPin, int echoPin);
    void init(int period);
    void tick();

private:
    int pin;
    WasteDetector *sonar;
    enum { EMPTY, PARTIAL, FULL } state;

};
