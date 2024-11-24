#include <Arduino.h>
#include "scheduler/scheduler.h"
#include "tasks/tempDetectTask.h"
#include "tasks/wasteDetectTask.h"
#include "tasks/userDetectTask.h"

#include "config.h"

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(SCHEDULER_BASE_PERIOD);

    Task *t0 = new TempDetectTask(TEMP_PIN);
    t0->init(TEMP_TASK_PERIOD);
    sched.addTask(t0);

    Task *t1 = new WasteDetectTask(WASTE_DET_TRIGGPIN, WASTE_DET_ECHOPIN);
    t1->init(WASTE_DET_TASK_PERIOD);
    sched.addTask(t1);

    Task *t2 = new UserDetectTask(USER_DET_PIN);
    t2->init(USER_DET_TASK_PERIOD);
    sched.addTask(t2);
}

void loop() {
    sched.schedule();
}
