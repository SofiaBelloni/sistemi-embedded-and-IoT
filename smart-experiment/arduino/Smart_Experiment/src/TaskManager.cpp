#include "TaskManager.h"

TaskManager* TaskManager::instance = 0;

TaskManager::TaskManager(){
    this->tasks.setStorage(this->storage_array);
}

int TaskManager::CalculateMCD(int x, int y){
    int r;
    if(y>x){
        r=y;
        y=x;
        x=r;
    }
    r = x % y;
    while(r>0){
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

void TaskManager::InitScheduler(Vector<int>* periods){
  int currMCD = CalculateMCD(periods->at(0), periods->at(1));
  for (unsigned i = 2; i < periods->size(); i++)
  {
    currMCD = CalculateMCD(currMCD, periods->at(i));
  }
  this->scheduler->init(currMCD);
}

void TaskManager::AddTask(String name, Task* task){
    taskStruct tmp;
    tmp.name = name;
    tmp.task = task;
    this->tasks.push_back(tmp);
}

void TaskManager::ResetSchedulerBasePeriod(int newPeriod){
    this->scheduler->init(this->CalculateMCD(this->scheduler->GetBasePeriod(), newPeriod));
}

void TaskManager::RemoveTask(String name){
    for (unsigned i = 0; i < this->tasks.size(); i++)
    {
        if (this->tasks.at(i).name.equals(name))
        {
            this->tasks.remove(i);
        }
    }
}

Task* TaskManager::GetTask(String name){
    for (unsigned i = 0; i < this->tasks.size(); i++)
    {
        if (this->tasks.at(i).name.equals(name))
        {
            return this->tasks.at(i).task;
        }
    }
    return NULL;
}

void TaskManager::SetTaskActive(String name, bool isActive){
    for (unsigned i = 0; i < this->tasks.size(); i++)
    {
        if (this->tasks.at(i).name.equals(name))
        {
            this->tasks.at(i).task->SetActive(isActive);
        }
    }
}

TaskManager* TaskManager::GetSingletonInstance(){
    if (instance == nullptr)
    {
        instance = new TaskManager();
    }
    return instance;
}
