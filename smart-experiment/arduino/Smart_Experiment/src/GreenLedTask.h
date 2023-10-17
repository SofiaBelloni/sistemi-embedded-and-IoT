#ifndef __GREEN_LED_TASK__
#define __GREEN_LED_TASK__

#include "Task.h"
#include "Led.h"

class GreenLedTask: public Task {
private:
  Light* greenLed;
  int time;
  enum {GL0, GL1, GL2} taskState;

  void GL0State();
  void GL1State();
  void GL2State();
  
public:
  GreenLedTask(int pin);
  void Tick();
};

#endif

