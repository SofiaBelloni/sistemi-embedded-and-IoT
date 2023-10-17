#include "Potentiometer.h"
#include <Arduino.h>
#include "Config.h"

Potentiometer* Potentiometer::instance = 0;

void Potentiometer::SetPin(int pin){
    this->pin = pin;
}

int Potentiometer::GetValue(){
    return 1000 / map(analogRead(pin), 0, 1023, 1, 50);
}

Potentiometer* Potentiometer::GetSingletonInstance(){
    if (instance == nullptr)
    {
        instance = new Potentiometer();
    }
    return instance;
}