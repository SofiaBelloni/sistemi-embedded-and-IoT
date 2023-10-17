#ifndef __SERIAL_MSG_SERVICE__
#define __SERIAL_MSG_SERVICE__

#include <Arduino.h>

class SerialMsgService
{

public:
    void Init();
    void sendMsg(String msg);
    bool isMsgAvailable();
    String receiveMsg();

private:
    String msgAvailable;
};
#endif