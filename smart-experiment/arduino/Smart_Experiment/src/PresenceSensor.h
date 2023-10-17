#ifndef __PRESENCE_SENSOR__
#define __PRESENCE_SENSOR__

class PresenceSensor{ 
public:
  virtual bool IsElementDetected() = 0;
};

#endif