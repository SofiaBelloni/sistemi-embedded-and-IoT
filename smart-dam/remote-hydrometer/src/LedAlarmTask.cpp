#include "LedAlarmTask.h"

LedAlarmTask::LedAlarmTask(int pin, HydrometerTask* hydrometerTask){
  this->hydrometerTask = hydrometerTask;
  this->led = new Led(pin);
  this->led->switchOff();
  this->state = OFF;
}

void LedAlarmTask::Tick(){
      switch (this->hydrometerTask->GetHydrometerState())
    {
        case HydrometerTask::NORMAL:
            if(this->state == ON){
                this->led->switchOff();
                this->state = OFF;
            }
            break;
        case HydrometerTask::PREALARM:
            if (this->state == ON)
            {
                this->led->switchOff();
                this->state = OFF;
            }else{
                this->led->switchOn();
                this->state = ON;
            }
            
            break;
        case HydrometerTask::ALARM:
            if(this->state == OFF){
                this->led->switchOn();
                this->state = ON;
            }
            break;
    }
}