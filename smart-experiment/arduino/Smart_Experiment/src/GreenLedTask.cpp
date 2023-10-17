#include "GreenLedTask.h"
#include "Config.h"
#include "TaskManager.h"
#include "ExperimentTask.h"
#include "DetectPresenceTask.h"
#include <avr/sleep.h>
#include "MsgService.h"

void WakeUp(){}

GreenLedTask::GreenLedTask(int pin){
  this->greenLed = new Led(pin);
  this->taskState = GL0;
  this->time = 0;
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), WakeUp, RISING);
}

void GreenLedTask::Tick(){
  switch (this->taskState)
  {
  case GL0:
    GL0State();
    break;

  case GL1:
    GL1State();
    break;

  case GL2:
    GL2State();
    break;
  
  default:
    break;
  }
}

void GreenLedTask::GL0State(){
  //led has to be on
  this->greenLed->switchOn();
  this->time += this->GetPeriod();
  // if SLEEP_TIME second has passed and a precence has not been detected 
  // --> switch to state GL2
  if ((this->time / 1000) >= SLEEP_TIME
  && !((DetectPresenceTask*)TaskManager::GetSingletonInstance()->GetTask(DETECT_PRESENCE_TASK))->IsPresenceDetected())
  {
    this->time = 0;
    this->taskState = GL2;
  }else if (((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState() == ExperimentTask::STARTED
  || ((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState() == ExperimentTask::ERROR)
  {
    // if the experiment is started or is in ERROR state --> switch to state GL1
    this->time = 0;
    this->taskState = GL1;
  }
}

void GreenLedTask::GL1State(){
  this->greenLed->switchOff();
  // if the experiment is ended and userConfirm has been received or if experiment in not in ERROR mode
  //--> switch to state GL0
  if (((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState() == ExperimentTask::INIT)
  {
    this->taskState = GL0;
  }
}

void GreenLedTask::GL2State(){
  this->greenLed->switchOff();
  MsgService::GetSingletonInstance()->Sleep();
  delay(100); //Without delay the serial print breaks
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();
  // When exit from sleep mode go to state GL0
  MsgService::GetSingletonInstance()->Wait();
  this->taskState = GL0;
}