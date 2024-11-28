#include "tasks/communicationsTask.h"
#include "communications/MsgService.h"

void CommunicationsTask::init(int period) {
    Task::init(period);
}

void CommunicationsTask::tick() {
    sendCurrentStates();
    delay(10);
    receiveUpdatedStates();
}

void CommunicationsTask::sendCurrentStates() {
    prepareCurrentStates();
    for (String state : currentStates) {
        MsgService.sendMsg(state);
    }
}

void CommunicationsTask::receiveUpdatedStates() {
    Msg *msg = MsgService.receiveMsg();
    if (msg == NULL) {
        return;
    }
    String type = msg->getContent().substring(0, 4);
    String content = msg->getContent().substring(5);

    if (type == DO_EMPTY_CONTAINER_TYPE)
        doEmptyContainer =  content == "true" ? true : false;
    if (type == TEMP_PROBLEM_DETECT_TYPE)
        tempProblemDetected = content == "true" ? true : false;
}

void CommunicationsTask::prepareCurrentStates() {
    currentStates[0] = String(CONTAINER_FULL_TYPE) + ":" + (isContainerFull ? "true" : "false");
    currentStates[1] = String(DO_EMPTY_CONTAINER_TYPE) + ":" + (doEmptyContainer ? "true" : "false");
    currentStates[2] = String(SLEEP_MODE_TYPE) + ":" + (sleepMode ? "true" : "false");
    currentStates[3] = String(TEMP_PROBLEM_DETECT_TYPE) + ":" + (tempProblemDetected ? "true" : "false");
    currentStates[4] = String(TEMPERATURE_TYPE) + ":" + temperature;

}



