#pragma once

#include "scheduler/task.h"
#include "hardware/temp.h"

#define MAX_TEMP 15.0
#define MAX_TIME_ON_HIGH_TEMP 10        // seconds

class TempDetectTask : public Task {
public:
    TempDetectTask(int pin);
    void init(int period);
    void tick();

private:
    int pin;
    Temp *temp;
    int timeOnHighTemp;
    int lastTimeCheck;
    enum { NORMAL_TEMP, HIGH_TEMP, PROBLEM_DETECTED } state;
};
