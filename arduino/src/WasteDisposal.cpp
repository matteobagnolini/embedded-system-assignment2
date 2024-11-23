#include <Arduino.h>
#include "scheduler/scheduler.h"
#include "tasks/tempDetectTask.h"
#include "tasks/wasteDetectTask.h"

#define BASE_PERIOD 50
#define TEMP_TASK_PERIOD 150
#define WASTE_DET_TASK_PERIOD 150

#define TEMP_PIN A0
#define WASTE_DET_TRIGGPIN 7
#define WASTE_DET_ECHOPIN 8

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(BASE_PERIOD);

    Task *t0 = new TempDetectTask(TEMP_PIN);
    t0->init(TEMP_TASK_PERIOD);
    sched.addTask(t0);

    Task *t1 = new WasteDetectTask(WASTE_DET_TRIGGPIN, WASTE_DET_ECHOPIN);
    t1->init(WASTE_DET_TASK_PERIOD);
    sched.addTask(t1);
}

void loop() {
    sched.schedule();
}
