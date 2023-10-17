#ifndef __SONAR_IMPL__
#define __SONAR_IMPL__

#include "Sonar.h"

class SonarImpl : public Sonar{ 
public:
  SonarImpl(int trigPin, int echoPin, float temperature); 
  // return the distance in m
  float GetDistance();

private:
  int trigPin;
  int echoPin;
  float vs;

};

#endif