#include <Arduino.h>
#include "scheduler/scheduler.h"
#include "tasks/tempDetectTask.h"

#define BASE_PERIOD 50

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(BASE_PERIOD);

  Task *t0 = new TempDetectTask(A0);
  t0->init(150);
  sched.addTask(t0);
}

void loop() {
  sched.schedule();
}
