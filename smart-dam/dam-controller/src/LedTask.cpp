#include "LedTask.h"

LedTask::LedTask(int pin)
{
    this->led = new Led(pin);
    this->led->switchOff();
    this->ledState = OFF;
}

void LedTask::Tick()
{
    switch (this->ledBehavior)
    {
    case OFF_FIXED:
        if (this->ledState == ON)
        {
            this->led->switchOff();
            this->ledState = OFF;
        }
        break;

    case BLINKING:
        if (this->ledState == ON)
        {
            this->led->switchOff();
            this->ledState = OFF;
        }
        else
        {
            this->led->switchOn();
            this->ledState = ON;
        }
        break;

    case ON_FIXED:
        if (this->ledState == OFF)
        {
            this->led->switchOn();
            this->ledState = ON;
        }
        break;
    }
}