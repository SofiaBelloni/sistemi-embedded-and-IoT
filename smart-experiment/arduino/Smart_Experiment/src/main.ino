#include <Arduino.h>
#include <Config.h>
#include "Scheduler.h"
#include "GreenLedTask.h"
#include "RedLedTask.h"
#include "BlinkTask.h"
#include "StartButtonTask.h"
#include "StopButtonTask.h"
#include "DetectPresenceTask.h"
#include "ExperimentTask.h"
#include "Potentiometer.h"
#include "MsgService.h"
#include "TaskManager.h"
#include "TemperatureSensor.h"
#include "TemperatureSensorImpl.h"
#include "Vector.h"

Scheduler* scheduler;
Vector<int> periods;

void initializeTask(Task* task, String name, int period, bool setActive){
  task->Init(period);
  task->SetActive(setActive);
  scheduler->addTask(task);
  TaskManager::GetSingletonInstance()->AddTask(name, task);
  periods.push_back(period);
}

void setup() {
  scheduler = new Scheduler();
  int storage_array[MAX_TASKS];
  periods.setStorage(storage_array);
  MsgService::GetSingletonInstance()->Init();

  //Initialize all tasks
  Task* greenLedTask = new GreenLedTask(LED_GREEN_PIN);
  initializeTask(greenLedTask, GREEN_LED_TASK, 100, true);

  Task* blinkTask = new BlinkTask(LED_RED_PIN);
  initializeTask(blinkTask, BLINK_TASK, 40, false);

  Task* redLedTask = new RedLedTask(LED_RED_PIN, blinkTask);
  initializeTask(redLedTask, RED_LED_TASK, 100, true);

  Task* startButton = new StartButtonTask(BUTTON_START_PIN);
  initializeTask(startButton, START_BUTTON_TASK, 100, true);

  Task* stopButton = new StopButtonTask(BUTTON_STOP_PIN);
  initializeTask(stopButton, STOP_BUTTON_TASK, 100, true);

  Task* detectPresence = new DetectPresenceTask(PIR_PIN);
  MsgService::GetSingletonInstance()->PirCalibration();
  ((DetectPresenceTask*)detectPresence)->CalibratePir(); //delay
  MsgService::GetSingletonInstance()->Wait();
  initializeTask(detectPresence, DETECT_PRESENCE_TASK, 100, true);

  Potentiometer::GetSingletonInstance()->SetPin(POT_PIN);

  TemperatureSensor* tmp = new TemperatureSensorImpl(TEMP_PIN);
  Task* experimentTask = new ExperimentTask(SONAR_TRIG_PIN, SONAR_ECHO_PIN, SERVO_PIN, tmp->GetTemperature());
  initializeTask(experimentTask, EXPERIMENT_TASK, 100, true);

  TaskManager::GetSingletonInstance()->SetScheduler(scheduler);
  TaskManager::GetSingletonInstance()->InitScheduler(&periods);
}

void loop() {
  scheduler->schedule();
}