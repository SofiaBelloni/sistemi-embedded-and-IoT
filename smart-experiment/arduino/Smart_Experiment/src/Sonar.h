#ifndef __SONAR__
#define __SONAR__

#include "PresenceSensor.h"

#define NOT_DETECTED -1

class Sonar : public PresenceSensor{ 
public: 
  virtual bool IsElementDetected() = 0;
  virtual float GetDistance() = 0;
};

#endif