#include "BTMsgService.h"

BTMsgService::BTMsgService(int rxPin, int txPin)
{
    this->channel = new SoftwareSerial(rxPin, txPin);
}

void BTMsgService::Init()
{
    this->channel->begin(9600);
    this->msgAvailable = "";
}

void BTMsgService::sendMsg(String msg)
{
    this->channel->println(msg);
}

bool BTMsgService::isMsgAvailable()
{
    return this->channel->available() != 0 ? true : false;
}

String BTMsgService::receiveMsg()
{
  return this->isMsgAvailable() ? this->channel->readStringUntil('\n') : "";
}
