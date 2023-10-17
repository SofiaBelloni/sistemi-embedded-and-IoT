#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer{ 
public:
  static Potentiometer* GetSingletonInstance();
  //Return period in milliseconds 
  int GetValue();
  void SetPin(int pin);

private:
  static Potentiometer *instance;
  int pin;  
};

#endif