#ifndef __PIR__
#define __PIR__

#include "PresenceSensor.h"

class Pir : public PresenceSensor { 
public:
  virtual bool IsElementDetected() = 0;
  virtual void Calibrate() = 0;
};

#endif