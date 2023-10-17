#ifndef __DAM_CONTROLLER_TASK__
#define __DAM_CONTROLLER_TASK__

#include <ArduinoJson.h>
#include "Task.h"
#include "ServoMotor.h"
#include "SerialMsgService.h"
#include "BTMsgService.h"
#include "LedTask.h"

class DamControllerTask : public Task
{
public:
    DamControllerTask(int servoPin, LedTask *ledTask, int rxPin, int txPin);
    void Tick();

private:
    enum
    {
        MANUAL,
        AUTO
    } damMode;

    LedTask *ledTask;
    ServoMotor *servo;
    SerialMsgService *serialMsg;
    BTMsgService *btMsg;
    StaticJsonDocument<200> jsonDoc;

    void InterpretBTCommand(String jsonMsg);
    void InterpretSerialCommand(String jsonMsg);
    int CalculateDamOpening();
};

#endif