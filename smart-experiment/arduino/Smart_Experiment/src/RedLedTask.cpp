#include "RedLedTask.h"
#include "Config.h"
#include "ExperimentTask.h"
#include "TaskManager.h"

RedLedTask::RedLedTask(int pin, Task* blinkTask){
  this->redLed = new Led(pin);
  this->taskState = RL0;
  this->blinkTask = blinkTask;
}

void RedLedTask::Tick(){
  switch (this->taskState)
  {
  case RL0:
    RL0State();
    break;

  case RL1:
    RL1State();
    break;

  case RL2:
    RL2State();
    break;
  
  default:
    break;
  }
}

void RedLedTask::RL0State(){
  this->redLed->switchOff();
  //check if the experiment is in the error state
  if (((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState()==ExperimentTask::ERROR)
  {
    this->taskState = RL2;
  //check if the experiment is started
  }else if (((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState()==ExperimentTask::STARTED)
  {
    this->taskState = RL1;
  }
}

void RedLedTask::RL1State(){
  this->redLed->switchOn();
  //check if the experiment is ended
  if (((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState()==ExperimentTask::ENDED)
  {
    this->taskState = RL2;
  }
}

void RedLedTask::RL2State(){
  this->blinkTask->SetActive(true);
  //if experiment status is not error disactive the blinking and go to state RL0 (init)
  if(((ExperimentTask*)TaskManager::GetSingletonInstance()->GetTask(EXPERIMENT_TASK))->GetExperimentState()==ExperimentTask::INIT){
    this->blinkTask->SetActive(false);
    this->taskState = RL0;
  }
}