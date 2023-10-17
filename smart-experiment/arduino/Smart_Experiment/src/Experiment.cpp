#include "Experiment.h"
#include <Arduino.h>
#include "Config.h"
#include "ServoMotorImpl.h"
#include "SonarImpl.h"

Experiment::Experiment(int sonarTrigPin, int sonarEchoPin, int servoPin, float temperature){
    this->sonar = new SonarImpl(sonarTrigPin, sonarEchoPin, temperature);
    this->servo = new ServoMotorImpl(servoPin);
    this->ResetExperiment();
}

void Experiment::UpdateValues(){
    float newPosition = this->sonar->GetDistance();
    float newTime = (float)(millis() / 1000.0);
    float newSpeed = (newPosition - this->position) / (newTime - this->time);
    this->acceleration = (newSpeed - this->speed) / (newTime - this->time);
    this->speed = newSpeed;
    this->position = newPosition;
    this->time = newTime;
    this->servo->SetAngle(map(this->speed, 0, MAXVEL, 0, 180));
}

float Experiment::GetPosition(){
    return this->position;
}

float Experiment::GetTime(){
    return (this->time - initialTime);
}

float Experiment::GetSpeed(){
    return this->speed;
}

float Experiment::GetAcceleration(){
    return this->acceleration;
}

void Experiment::ResetExperiment(){
    this->time = millis() / 1000;
    this->initialTime = this->time;
    this->position = 0.0;
    this->speed = 0.0;
    this->acceleration = 0.0;
}