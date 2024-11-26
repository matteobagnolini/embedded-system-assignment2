#pragma once

#include "hardware/sonar.h"
#include "scheduler/task.h"

#define THRESHOLD_DISTANCE 0.50     // meters
#define EMPTY_DISTANCE 2.0

class WasteDetectTask : public Task {

public:
    WasteDetectTask(int triggPin, int echoPin);
    void init(int period);
    void tick();

private:
    int pin;
    Sonar *sonar;
    enum { EMPTY, PARTIAL, FULL } state;

};
