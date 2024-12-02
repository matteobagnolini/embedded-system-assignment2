#pragma once

#include "scheduler/task.h"
#include "hardware/temp.h"

#define MAX_TEMP 18.0
#define MAX_TIME_ON_HIGH_TEMP_SEC 5

class TempDetectTask : public Task {

public:
    TempDetectTask(int pin);
    void init(int period);
    void tick();

private:
    int pin;
    TempDetector *temp;
    int timeOnHighTemp;
    int lastTimeCheck;
    enum { NORMAL_TEMP, HIGH_TEMP, PROBLEM_DETECTED } state;

};
