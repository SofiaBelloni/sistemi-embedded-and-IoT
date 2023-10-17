#ifndef __LED_TASK__
#define __LED_TASK__

#include "Task.h"
#include "Led.h"

class LedTask : public Task
{

public:
  enum behavior
  {
    ON_FIXED,
    BLINKING,
    OFF_FIXED
  };
  LedTask(int pin);
  void Tick();
  void setBehavior(behavior behavior) { this->ledBehavior = behavior; }

private:
  Light *led;
  enum
  {
    ON,
    OFF
  } ledState;
  behavior ledBehavior;
};

#endif