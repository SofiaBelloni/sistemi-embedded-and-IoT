#include "StopButtonTask.h"
#include "Config.h"

StopButtonTask::StopButtonTask(int pin){
  this->btn = new ButtonImpl(pin);
  this->isBtnPressed = false;
}

void StopButtonTask::Tick(){
  this->isBtnPressed = this->btn->isPressed() ? true : false;
}

bool StopButtonTask::IsBtnPressed(){
  return this->isBtnPressed;
}