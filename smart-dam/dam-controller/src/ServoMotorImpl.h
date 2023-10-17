#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include "ServoTimer2.h"

class ServoMotorImpl : public ServoMotor
{
public:
  ServoMotorImpl(int pin);
  void SetAngle(int angle);
  void On();
  void Off();

private:
  int pin;
  ServoTimer2 servo;
};

#endif