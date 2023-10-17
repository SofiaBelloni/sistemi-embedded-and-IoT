#ifndef __LED_ALARM_TASK__
#define __LED_ALARM_TASK__

#include "Task.h"
#include "Led.h"
#include "HydrometerTask.h"

class LedAlarmTask : public Task {
  
private:
  Light* led;
  HydrometerTask* hydrometerTask;
  enum { ON, OFF} state;
public:
  LedAlarmTask(int pin, HydrometerTask* hydrometerTask);
  void Tick();
};

#endif