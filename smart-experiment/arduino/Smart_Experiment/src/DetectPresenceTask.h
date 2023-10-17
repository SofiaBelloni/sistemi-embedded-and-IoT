#ifndef __DETECT_PRESENCE_TASK__
#define __DETECT_PRESENCE_TASK__

#include "Task.h"
#include "Pir.h"

class DetectPresenceTask: public Task {
public:
  DetectPresenceTask(int pin);
  bool IsPresenceDetected();
  void CalibratePir(){this->pir->Calibrate();}
  void Tick();
private:
  Pir* pir;
  bool presence;
};

#endif

