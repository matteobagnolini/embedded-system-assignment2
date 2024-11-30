#include <Arduino.h>
#include "scheduler/scheduler.h"
#include "tasks/tempDetectTask.h"
#include "tasks/wasteDetectTask.h"
#include "tasks/userDetectTask.h"
#include "tasks/wasteDisposalTask.h"
#include "tasks/communicationsTask.h"

#include "config.h"

Scheduler sched;

bool isContainerFull, sleepMode, tempProblemDetected, isTempProblemResolved, doEmptyContainer;
float temperature, fillingPercentage;

void setup() {
    Serial.begin(9600);
    sched.init(SCHEDULER_BASE_PERIOD);

    Task *tempDetectTask = new TempDetectTask(TEMP_PIN);
    tempDetectTask->init(TEMP_TASK_PERIOD);
    sched.addTask(tempDetectTask);

    Task *wasteDetectTask = new WasteDetectTask(WASTE_DET_TRIGGPIN, WASTE_DET_ECHOPIN);
    wasteDetectTask->init(WASTE_DET_TASK_PERIOD);
    sched.addTask(wasteDetectTask);

    Task *userDetectTask = new UserDetectTask(USER_DET_PIN);
    userDetectTask->init(USER_DET_TASK_PERIOD);
    sched.addTask(userDetectTask);

    Task *wasteDisposalTask = new WasteDisposalTask(
                                     GREEN_LED_PIN,
                                     RED_LED_PIN,
                                     OPEN_BUTTON_PIN,
                                     CLOSE_BUTTON_PIN,
                                     SERVO_MOTOR_PIN
                                    );
    wasteDisposalTask->init(WASTE_DISP_TASK_PERIOD);
    sched.addTask(wasteDisposalTask);

    Task *communicationsTask = new CommunicationsTask();
    communicationsTask->init(COMM_TASK_PERIOD);
    sched.addTask(communicationsTask);
}

void loop() {
    sched.schedule();
}
