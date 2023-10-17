#include "PirImpl.h"
#include "Arduino.h"

PirImpl::PirImpl(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

bool PirImpl::IsElementDetected(){
    return digitalRead(pin) == HIGH ? true : false; 
}
// 10 seconds delay used to calibrate sensor, must be called in setup
void PirImpl::Calibrate(){
    delay(10000);
}