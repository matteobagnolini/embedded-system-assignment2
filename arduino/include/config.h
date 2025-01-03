/* ********* Configuration File ********* */

#pragma once

/* =========== TASKS PERIODS =========== */
#define SCHEDULER_BASE_PERIOD 50
#define TEMP_TASK_PERIOD 150
#define WASTE_DET_TASK_PERIOD 150
#define USER_DET_TASK_PERIOD 150
#define WASTE_DISP_TASK_PERIOD 150
#define COMM_TASK_PERIOD 750

/* =========== DEVICES PINS =========== */
#define TEMP_PIN A0
#define WASTE_DET_TRIGGPIN 7
#define WASTE_DET_ECHOPIN 8
#define USER_DET_PIN 2
#define SERVO_MOTOR_PIN 3
#define GREEN_LED_PIN 12
#define RED_LED_PIN 13
#define OPEN_BUTTON_PIN 11
#define CLOSE_BUTTON_PIN 10
