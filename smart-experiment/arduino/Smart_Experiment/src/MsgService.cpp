#include "Arduino.h"
#include "MsgService.h"

String content;

MsgService* MsgService::instance = 0;

MsgService* MsgService::GetSingletonInstance(){
    if (instance == nullptr)
    {
        instance = new MsgService();
    }
    return instance;
}


bool MsgService::isMsgAvailable(){
  return msgAvailable;
}

Msg* MsgService::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;  
  } else {
    return NULL; 
  }
}

void MsgService::Init(){
  Serial.begin(115200);
  content.reserve(256);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;  
}

void MsgService::sendMsg(const String& msg){
  fflush(stdout);
  Serial.println(msg);  
  fflush(stdout);
}

//called at the end of every loop
void serialEvent() {
  /* reading the content */
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\n'){
      MsgService::GetSingletonInstance()->SetCurrentMsg(new Msg(content));
      MsgService::GetSingletonInstance()->SetMsgAvailable(true);      
    } else {
      content += ch;      
    }
  }
}
  
//Return true when "ok" is received from the serial.
bool MsgService::ConfirmationReceived() {
  if (isMsgAvailable()) {
    Msg* msg = receiveMsg();    
    if (msg->getContent() == "ok") {
      delete msg;
      return true;
    }
    delete msg;
  }
  return false;
}

//Send start message to the serial
void MsgService::Start(){
  sendMsg("start");
}

//Send end message to the serial
void MsgService::End(){
  sendMsg("end");
}

//Send error message to the serial
void MsgService::Error(){
  sendMsg("error");
}

//Send wait message to the serial. call this after error and after experiment end
void MsgService::Wait(){
  sendMsg("wait");
}

//Send sleep message to the serial. call this when arduino go in sleep mode
void MsgService::Sleep(){
  sendMsg("sleep");
}

//Send pir_calibration message to the serial. call this during the pir calibration
void MsgService::PirCalibration(){
  sendMsg("pir");
}

//Send Position Value to the serial (will send a string like this: p_0.32;t_1220)
void MsgService::SendPositionValue(double value, double time){
  sendMsg(String("p_") + value + String(";t_") + time);
}
//Send Speed Value to the serial (will send a string like this: s_5;t_1220)
void MsgService::SendSpeedValue(double value, double time){
  sendMsg(String("s_") + value + String(";t_") + time);
}
//Send Acceleration Value to the serial (will send a string like this: a_52;t_1220)
void MsgService::SendAccelerationValue(double value, double time){
  sendMsg(String("a_") + value + String(";t_") + time);
}
