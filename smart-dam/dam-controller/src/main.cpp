#include <Arduino.h>
#include "Config.h"
#include "Scheduler.h"
#include "LedTask.h"
#include "DamControllerTask.h"

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

void setup()
{
  scheduler = new Scheduler();
  LedTask* ledTask = new LedTask(LED_PIN);
  DamControllerTask* damTask = new DamControllerTask(SERVO_PIN, ledTask, BLUETOOTH_RXT, BLUETOOTH_RXD);
  initializeTask(ledTask, LED_PERIOD, true);
  initializeTask(damTask, DAM_CONTROLLER_PERIOD, true);
  scheduler->init(calculateMCD(LED_PERIOD, DAM_CONTROLLER_PERIOD));
}

void loop()
{
  scheduler->schedule();
}