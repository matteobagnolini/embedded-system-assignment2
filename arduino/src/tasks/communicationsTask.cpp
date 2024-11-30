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
    MsgService.sendMsg(String(CONTAINER_FULL_TYPE) + (isContainerFull ? ":true" : ":false"));
    MsgService.sendMsg(String(TEMP_PROBLEM_DETECT_TYPE) + (tempProblemDetected ? ":true" : ":false"));
    MsgService.sendMsg(String(TEMPERATURE_TYPE) + ":" + temperature);
    MsgService.sendMsg(String(FILLING_PERC_TYPE) + ":" + fillingPercentage);
}

void CommunicationsTask::receiveUpdatedStates() {
    Msg *msg = MsgService.receiveMsg();
    if (msg == NULL) {
        return;
    }
    String header = msg->getContent().substring(0, 4);
    String content = msg->getContent().substring(5);

    if (header == DO_EMPTY_CONTAINER_TYPE)
        doEmptyContainer =  content == "true" ? true : false;
    if (header == TEMP_PROBLEM_DETECT_TYPE)
        tempProblemDetected = content == "true" ? true : false;
}
