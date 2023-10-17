#ifndef __START_BUTTON_TASK__
#define __START_BUTTON_TASK__

#include "Task.h"
#include "ButtonImpl.h"

class StartButtonTask: public Task {
private:
  Button* btn;
  bool isBtnPressed;
public:
  StartButtonTask(int pin);
  bool IsBtnPressed();
  void Tick();
};

#endif

