/* ********** Global Variables File ********** */

#pragma once

/* ============ Global Variables ============ */

#define NUM_GLOBAL_VARIABLES 5

/* ============ Communication Headers ============ */
/* These symbols are used as an header for serial communication messages */
#define CONTAINER_FULL_HEADER "CNTF"
#define DO_EMPTY_CONTAINER_HEADER "CNTE"
#define TEMP_PROBLEM_DETECT_HEADER "TMPP"
#define TEMPERATURE_HEADER "TEMP"
#define FILLING_PERC_HEADER "FILL"

/* These variables are used to permit the comunication between different tasks */
extern bool isContainerFull;
extern bool doEmptyContainer;
extern bool sleepMode;
extern bool tempProblemDetected;
extern float temperature;
extern float fillingPercentage;