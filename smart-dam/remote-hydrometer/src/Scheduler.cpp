#include "Scheduler.h"
#include <Arduino.h>

volatile bool timerFlag;

void timerHandler(){
  timerFlag = true;
}

Scheduler::Scheduler(){
  nTasks = 0;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  this->ticker.attach(0.1, timerHandler);
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){
  while (!timerFlag){yield();}

  timerFlag = false;
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->IsActive() && taskList[i]->UpdateAndCheckTime(basePeriod)){
      taskList[i]->Tick();
    }
  }
}
