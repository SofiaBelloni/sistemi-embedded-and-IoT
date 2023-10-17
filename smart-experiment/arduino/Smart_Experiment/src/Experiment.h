#ifndef __EXPERIMENT__
#define __EXPERIMENT__

#include "Sonar.h"
#include "ServoMotor.h"

class Experiment{
private:
    Sonar* sonar;
    ServoMotor* servo;
    float time;
    float initialTime;
    float position;
    float speed;
    float acceleration;

public:
    void UpdateValues();
    Experiment(int sonarTrigPin, int sonarEchoPin, int servoPin, float temperature);
    // return position in m
    float GetPosition();
    //returns the seconds from the beginning of the experiment
    float GetTime();
    //return speed in m/s
    float GetSpeed();
    //return acceleration in m/s^2
    float GetAcceleration();

    void ResetExperiment();

    bool isObjectDetected(){return this->sonar->IsElementDetected();}
    //Return the servo
    ServoMotor* GetServo(){return this->servo;}
};

#endif
