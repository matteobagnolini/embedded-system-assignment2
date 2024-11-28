#pragma once

/* ============ Global Variables ============ */

#define NUM_GLOBAL_VARIABLES 4

/* Those variables are used to permit the comunication between different tasks */

extern bool isContainerFull;
extern bool doEmptyContainer;
extern bool sleepMode;
extern bool tempProblemDetected;
extern float temperature;