#include "tasks/communicationsTask.h"
#include "communications/MsgService.h"

void CommunicationsTask::init(int period) {
    Task::init(period);
}

void CommunicationsTask::tick() {
    sendCurrentStates();
    receiveUpdatedStates();
}

void CommunicationsTask::sendCurrentStates() {
    /* Messages are sent only if problems are detected */
    if (isContainerFull) {
        MsgService.sendMsg(String(CONTAINER_FULL_TYPE) + ":true");
    }
    if (sleepMode) {
        MsgService.sendMsg(String(SLEEP_MODE_TYPE) + ":true");
    }
    if (tempProblemDetected) {
        MsgService.sendMsg(String(TEMP_PROBLEM_DETECT_TYPE) + ":true");
    }
    MsgService.sendMsg(String(TEMPERATURE_TYPE) + ":" + temperature);
    MsgService.sendMsg(String(FILLING_PERC_TYPE) + ":" + fillingPercentage);
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
