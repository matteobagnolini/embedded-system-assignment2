#pragma once

#include "scheduler/task.h"
#include <Arduino.h>
#include "globals.h"

class CommunicationsTask : public Task {

public:
    void init(int period);
    void tick();

private:
    String currentStates[NUM_GLOBAL_VARIABLES];
    void sendCurrentStates();
    void receiveUpdatedStates();
    void prepareCurrentStates();

};
