#include <Arduino.h>
#include "scheduler.h"

#define BASE_PERIOD 50

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(BASE_PERIOD);
}

void loop() {
  sched.schedule();
}
