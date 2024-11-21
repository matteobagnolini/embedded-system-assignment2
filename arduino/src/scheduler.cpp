#include "scheduler/scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void) {
    timerFlag = true;
}

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    timerFlag = false;
    long period = 1000*basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(timerHandler);
    nTasks = 0;
}

bool Scheduler::addTask(Task *task) {
    if (nTasks < MAX_TASKS-1) {
        taskList[nTasks] = task;
        return true;
    }
    return false;
}

void Scheduler::schedule() {
    while (!timerFlag) {}   // Wait for next period elapsed
    timerFlag = false;

    for (int i = 0; i < nTasks; i++) {
        if (taskList[i]->updateAndCheckTime(basePeriod)) {
            taskList[i]->tick();
        }
    }
}