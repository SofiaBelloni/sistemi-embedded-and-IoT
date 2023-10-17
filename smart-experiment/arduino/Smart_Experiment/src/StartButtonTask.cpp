#include "StartButtonTask.h"
#include "Config.h"

StartButtonTask::StartButtonTask(int pin){
  this->btn = new ButtonImpl(pin);
  this->isBtnPressed = false;
}

void StartButtonTask::Tick(){
    this->isBtnPressed = this->btn->isPressed() ? true : false;
}

bool StartButtonTask::IsBtnPressed(){
  return this->isBtnPressed;
}