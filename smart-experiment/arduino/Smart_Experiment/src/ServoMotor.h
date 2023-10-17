#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor { 
public:
  virtual void SetAngle(int angle) = 0;
  virtual void On() = 0;
  virtual void Off() = 0;
};

#endif