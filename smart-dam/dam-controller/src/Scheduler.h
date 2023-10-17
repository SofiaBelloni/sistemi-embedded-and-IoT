#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 5

class Scheduler
{

  int basePeriod;
  int nTasks;
  Task *taskList[MAX_TASKS];

public:
  //basePeriod in milliseconds
  Scheduler();
  void init(int basePeriod);
  int GetBasePeriod() { return this->basePeriod; }
  virtual bool addTask(Task *task);
  virtual void schedule();
};

#endif
