#ifndef __HYDROMETER_TASK__
#define __HYDROMETER_TASK__

#include "Task.h"
#include "Sonar.h"
#include "Arduino.h"
#include "ConnectionManager.h"

class HydrometerTask: public Task {
public:
    enum state {NORMAL, PREALARM, ALARM};
    HydrometerTask(int trigPin, int echoPin, float temperature);
    void Tick();
    state GetHydrometerState();
private:
    Sonar* sonar;
    state currentState;
    float waterLevel;
    int time;
    ConnectionManager* connection;
    void UpdateState();
    void CreateAndSendMessage();
    String getStateString();
};

#endif