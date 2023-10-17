#ifndef __MSG_SERVICE__
#define __MSG_SERVICE__

#include "Arduino.h"

class Msg {
  String content;

public:
  Msg(String content){
    this->content = content;
  }
  
  String getContent(){
    return content;
  }
};

class MsgService {

public: 

  static MsgService* GetSingletonInstance();

  //do MsgService.init() in the setup
  void Init();  

  //Send start message to the serial
  void Start();
  //Send end message to the serial
  void End();
  //Send error message to the serial
  void Error();
  //Send wait message to the serial. call this after error and after experiment end
  void Wait();
  //Send sleep message to the serial. call this when arduino go in sleep mode
  void Sleep();
  //Send pir_calibration message to the serial. call this during the pir calibration
  void PirCalibration();
  //Send Position Value to the serial (will send a string like this: p_0.32;t_1220)
  void SendPositionValue(double value, double time);
  //Send Speed Value to the serial (will send a string like this: s_5;t_1220)
  void SendSpeedValue(double value, double time);
  //Send Acceleration Value to the serial (will send a string like this: a_52;t_1220)
  void SendAccelerationValue(double value, double time);
  
  //Return true when "ok" is received from the serial. to do a while(ConfirmationReceived())
  bool ConfirmationReceived();

  void SetCurrentMsg(Msg* message){this->currentMsg=message;}
  void SetMsgAvailable(bool value){this->msgAvailable=value;}

  
private:
  Msg* currentMsg;
  bool msgAvailable;
  static MsgService *instance;
  bool isMsgAvailable();
  Msg* receiveMsg();
  void sendMsg(const String& msg);

};

#endif