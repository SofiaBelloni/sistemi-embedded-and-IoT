#include "ServoMotorImpl.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;
}

 void ServoMotorImpl::On(){
  this->servo.attach(pin);
}

void ServoMotorImpl::Off(){
  this->servo.detach();
}

void ServoMotorImpl::SetAngle(int angle){
  /* 750 -> 0°
  *  2250 -> 180°
  */
  float coeff = (2250.0 - 750.0) / 180;
  this->servo.write(750 + angle * coeff);
}