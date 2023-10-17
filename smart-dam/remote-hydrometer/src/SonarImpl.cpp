#include "SonarImpl.h"
#include "Arduino.h"
#include "Config.h"

SonarImpl::SonarImpl(int trigPin, int echoPin, float temperature){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    vs = 331.45 + 0.62 * temperature;
}

float SonarImpl::GetDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * vs;
    return d;
}
