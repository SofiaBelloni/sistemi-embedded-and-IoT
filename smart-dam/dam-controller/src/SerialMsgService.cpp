#include "SerialMsgService.h"

void SerialMsgService::Init()
{
    Serial.begin(115200);
    this->msgAvailable = "";
}

void SerialMsgService::sendMsg(String msg)
{
    fflush(stdout);
    Serial.println(msg);
    fflush(stdout);
}

bool SerialMsgService::isMsgAvailable()
{
    return Serial.available() != 0 ? true : false;
}

String SerialMsgService::receiveMsg()
{
  return this->isMsgAvailable() ? Serial.readStringUntil('\n') : "";
}