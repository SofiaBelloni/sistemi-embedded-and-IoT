#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin){
  led = new Led(pin); 
  state = OFF;
}
  
void BlinkTask::Tick(){
  switch (state){
    case OFF:
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}
