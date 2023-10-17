#include <Arduino.h>
#include "TemperatureSensorImpl.h"
#include "HydrometerTask.h"
#include "LedAlarmTask.h"
#include "Config.h"
#include "Scheduler.h"

Scheduler* scheduler;

int calculateMCD(int x, int y){
    int r;
    if(y>x){
        r=y;
        y=x;
        x=r;
    }
    r = x % y;
    while(r>0){
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

void initializeTask(Task* task, int period, bool setActive){
  task->Init(period);
  task->SetActive(setActive);
  scheduler->addTask(task);
}

void setup() { 
  Serial.begin(115200);
  scheduler = new Scheduler();
  TemperatureSensor* tempSensor = new TemperatureSensorImpl(TEMP_PIN);
  HydrometerTask* hydrometerTask = new HydrometerTask(SONAR_TRIG_PIN, SONAR_ECHO_PIN, tempSensor->GetTemperature());
  LedAlarmTask* ledAlarmTask = new LedAlarmTask(LED_ALARM, hydrometerTask);
  initializeTask(ledAlarmTask, BLINKING_PERIOD, true);
  initializeTask(hydrometerTask, HYDROMETER_PERIOD, true);
  scheduler->init(calculateMCD(HYDROMETER_PERIOD, BLINKING_PERIOD));
} 
   
void loop() { 
  scheduler->schedule();
}