#include <Arduino.h>
#include "scheduler/scheduler.h"
#include "tasks/tempDetectTask.h"
#include "tasks/wasteDetectTask.h"
#include "tasks/userDetectTask.h"
#include "tasks/wasteDisposalTask.h"

#include "config.h"

Scheduler sched;

bool isContainerFull, sleepMode, tempProblemDetected, isTempProblemResolved, doEmptyContainer;
float temperature;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting program");
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

    Task *t3 = new WasteDisposalTask(
                                     GREEN_LED_PIN,
                                     RED_LED_PIN,
                                     OPEN_BUTTON_PIN,
                                     CLOSE_BUTTON_PIN,
                                     SERVO_MOTOR_PIN
                                    );
    t3->init(WASTE_DISP_TASK_PERIOD);
    sched.addTask(t3);
    Serial.println("Starting program...");
}

void loop() {
    sched.schedule();
}
