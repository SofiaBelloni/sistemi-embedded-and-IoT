#include "SonarImpl.h"
#include "HydrometerTask.h"
#include "Config.h"
#include <Arduino.h>

HydrometerTask::HydrometerTask(int trigPin, int echoPin, float temperature){
    this->sonar = new SonarImpl(trigPin, echoPin, temperature);
    this->currentState = NORMAL;
    this->time = 0;
    this->connection = new ConnectionManager(SSID_NAME, PASSWORD);
}

void HydrometerTask::UpdateState(){
    float distance = this->sonar->GetDistance() * 100;
    this->waterLevel = MAX_LEVEL - distance;
    if (distance > PREALARM_THRESHOLD && this->currentState != NORMAL)
    {
        this->currentState = NORMAL;
        this->CreateAndSendMessage();
    }
    if (distance < ALARM_THRESHOLD && this->currentState != ALARM){
        this->time = 0;
        this->currentState = ALARM;
        this->CreateAndSendMessage();
    }
    if(this->currentState != PREALARM
    && distance < PREALARM_THRESHOLD
    && distance > ALARM_THRESHOLD){
        this->time = 0;
        this->currentState = PREALARM;
        this->CreateAndSendMessage();
    }
    //this->currentState = (distance > PREALARM_THRESHOLD) ? NORMAL : ((distance < ALARM_THRESHOLD) ? ALARM : PREALARM);
}

String HydrometerTask::getStateString(){
    switch (this->currentState)
    {
        case NORMAL:
            return "NORMAL";
            break;
        case PREALARM:
            return "PREALARM";
            break;
        case ALARM:
            return "ALARM";
            break;
    }
}

void HydrometerTask::CreateAndSendMessage(){
    this->time = 0;

    //Build the string message
    String msg = String("{ \"command\": \"add_detection\", \"water_level\": ") + String(this->waterLevel) + ", \"state\": \"" + this->getStateString() +"\" }";
    this->connection->SendData(ADDRESS, msg.c_str());
}

void HydrometerTask::Tick(){
    UpdateState();
    this->time += this->GetPeriod();
    switch (this->currentState)
    {
    case PREALARM:
        if (this->time >= PREALARM_FREQ*1000)
        {
            this->CreateAndSendMessage();
        }
        break;

    case ALARM:
        if (this->time >= ALARM_FREQ*1000)
        {
            this->CreateAndSendMessage();
        }
        break;

    default:
        break;
    }
}

HydrometerTask::state HydrometerTask::GetHydrometerState(){
    return this->currentState;
}
