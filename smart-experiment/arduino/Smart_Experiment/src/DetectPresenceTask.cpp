#include "DetectPresenceTask.h"
#include "PirImpl.h"

DetectPresenceTask::DetectPresenceTask(int pin){
  pir = new PirImpl(pin);
  this->presence = false;
}
  
void DetectPresenceTask::Tick(){
  this->presence = this->pir->IsElementDetected() ? true : false;
}

bool DetectPresenceTask::IsPresenceDetected(){
  return this->presence;
}