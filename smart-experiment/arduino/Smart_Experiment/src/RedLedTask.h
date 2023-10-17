#ifndef __RED_LED_TASK__
#define __RED_LED_TASK__

#include "Task.h"
#include "Led.h"
#include "BlinkTask.h"

class RedLedTask: public Task {
private:
  Light* redLed;
  Task* blinkTask;
  enum {RL0, RL1, RL2} taskState;

  //RL0 is Init state
  void RL0State();
  //RL1 is Started state
  void RL1State();
  //RL2 is Error and Ended state
  void RL2State();
  
public:
  RedLedTask(int pin, Task* blinkTask);  
  void Tick();
};

#endif