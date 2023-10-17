#include "TemperatureSensorImpl.h"
#include "Config.h"
#include "Arduino.h"

TemperatureSensorImpl::TemperatureSensorImpl(int pin){
  this->pin = pin;
}

float TemperatureSensorImpl::GetTemperature(){
  int value = analogRead(this->pin);
  float valueInVolt = value * VCC / 1023;
  return valueInVolt/0.01;
}
