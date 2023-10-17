#ifndef __STOP_BUTTON_TASK__
#define __STOP_BUTTON_TASK__

#include "Task.h"
#include "ButtonImpl.h"

class StopButtonTask: public Task {
private:
  Button* btn;
  bool isBtnPressed;
public:
  StopButtonTask(int pin);
  bool IsBtnPressed();
  void Tick();
};

#endif

