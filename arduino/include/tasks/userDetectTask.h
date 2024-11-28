#pragma once

#include "scheduler/task.h"
#include "hardware/pir.h"

#define TIME_BEFORE_SLEEP_SEC 5

class UserDetectTask : public Task {

public:
    UserDetectTask(int pin);
    void init(int period);
    void tick();

private:
    Pir *pir;
    int timeElapsedNoDetection;
    int lastTimeCheck;
    enum { SLEEP, READY } state;

};
