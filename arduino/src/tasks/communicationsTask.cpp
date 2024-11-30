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
    MsgService.sendMsg(String(CONTAINER_FULL_HEADER) + (isContainerFull ? ":true" : ":false"));
    MsgService.sendMsg(String(TEMP_PROBLEM_DETECT_HEADER) + (tempProblemDetected ? ":true" : ":false"));
    MsgService.sendMsg(String(TEMPERATURE_HEADER) + ":" + temperature);
    MsgService.sendMsg(String(FILLING_PERC_HEADER) + ":" + fillingPercentage);
}

void CommunicationsTask::receiveUpdatedStates() {
    Msg *msg = MsgService.receiveMsg();
    if (msg == NULL) {
        return;
    }
    String header = msg->getContent().substring(0, 4);
    String content = msg->getContent().substring(5);

    if (header == DO_EMPTY_CONTAINER_HEADER)
        doEmptyContainer =  content == "true" ? true : false;
    if (header == TEMP_PROBLEM_DETECT_HEADER)
        tempProblemDetected = content == "true" ? true : false;
}
