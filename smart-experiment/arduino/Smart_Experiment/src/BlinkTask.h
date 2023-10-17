#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {
private:
  Light* led;
  enum { ON, OFF} state;
public:
  BlinkTask(int pin);
  void Tick();
};

#endif

