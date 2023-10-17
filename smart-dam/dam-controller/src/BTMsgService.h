#ifndef __BT_MSG_SERVICE__
#define __BT_MSG_SERVICE__

#include "SoftwareSerial.h"

class BTMsgService
{

public:
    BTMsgService(int rxPin, int txPin);
    void Init();
    void sendMsg(String msg);
    bool isMsgAvailable();
    String receiveMsg();

private:
    String msgAvailable;
    SoftwareSerial *channel;
};
#endif