#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

Scheduler::Scheduler(){
  nTasks = 0;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
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
  while (!timerFlag){}
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->IsActive() && taskList[i]->UpdateAndCheckTime(basePeriod)){
      taskList[i]->Tick();
    }
  }
}
