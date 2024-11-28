#pragma once

/* ============ Global Variables ============ */

#define NUM_GLOBAL_VARIABLES 5

/* ============ Communication Types ============ */
/* These symbols are used as an header for serial communications */
#define CONTAINER_FULL_TYPE "CNTF"
#define DO_EMPTY_CONTAINER_TYPE "CNTE"
#define SLEEP_MODE_TYPE "SLPM"
#define TEMP_PROBLEM_DETECT_TYPE "TMPP"
#define TEMPERATURE_TYPE "TEMP"

/* These variables are used to permit the comunication between different tasks */
extern bool isContainerFull;
extern bool doEmptyContainer;
extern bool sleepMode;
extern bool tempProblemDetected;
extern float temperature;