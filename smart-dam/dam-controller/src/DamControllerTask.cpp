#include <Arduino.h>
#include "DamControllerTask.h"
#include "ServoMotorImpl.h"
#include "Config.h"

DamControllerTask::DamControllerTask(int servoPin, LedTask *ledTask, int rxPin, int txPin)
{
    this->damMode = AUTO;
    this->servo = new ServoMotorImpl(servoPin);
    this->servo->On();
    this->ledTask = ledTask;
    this->btMsg = new BTMsgService(rxPin, txPin);
    this->btMsg->Init();
    this->serialMsg = new SerialMsgService();
    this->serialMsg->Init();
    this->ledTask->setBehavior(LedTask::behavior::OFF_FIXED);
}

void DamControllerTask::Tick()
{
    //check if a BTmessage is available
    if (this->btMsg->isMsgAvailable())
    {
        String msgBody = this->btMsg->receiveMsg();
        this->InterpretBTCommand(msgBody);
    }

    //check if a SerialMessage is available
    if (this->serialMsg->isMsgAvailable())
    {
        String msgBody = this->serialMsg->receiveMsg();
        this->InterpretSerialCommand(msgBody);
    }
    //request data to server
    this->serialMsg->sendMsg(String("{\"command\":\"get_last_detection\"}"));
}

void DamControllerTask::InterpretBTCommand(String msgBody)
{
    this->jsonDoc.clear();
    // Deserializing and test if parsing succeeds
    if (!deserializeJson(this->jsonDoc, msgBody))
    {
        //Interpret the command received(set_mode or set_opening)
        String command = this->jsonDoc["command"];
        if (command.equals("set_mode"))
        {
            if (this->jsonDoc["mode"] == "MANUAL")
            {
                this->damMode = MANUAL;
                //communicate it to ledTask
                this->ledTask->setBehavior(LedTask::behavior::ON_FIXED);
            }
            // the mode is AUTO
            else
            {
                this->damMode = AUTO;
            }
        }
        else if (command.equals("set_dam_opening"))
        {
            if(this->damMode == MANUAL)
                //set servo motor, map 0-100% to 0-180 degrees
                this->servo->SetAngle(map(this->jsonDoc["dam_opening"], 0, 100, 0, 180));
        }
        //forward the json received from bluetooth to the server
        this->serialMsg->sendMsg(msgBody);
    }
}

void DamControllerTask::InterpretSerialCommand(String jsonMsg)
{
    this->jsonDoc.clear();
    // Deserializing and test if parsing succeeds
    if (!deserializeJson(this->jsonDoc, jsonMsg))
    {
        if (this->jsonDoc["state"] == "ALARM" && this->damMode == MANUAL)
        {
            this->ledTask->setBehavior(LedTask::behavior::ON_FIXED);
        }
        else if (this->jsonDoc["state"] == "ALARM" && this->damMode == AUTO)
        {
            this->ledTask->setBehavior(LedTask::behavior::BLINKING);
            int damOpening = this->CalculateDamOpening();
            this->servo->SetAngle(map(damOpening, 0, 100, 0, 180));
            this->serialMsg->sendMsg(String("{\"command\":\"set_dam_opening\", \"dam_opening\":" + String(damOpening) + " }"));
        }
        else
        {
            this->ledTask->setBehavior(LedTask::behavior::OFF_FIXED);
        }
    }
}

int DamControllerTask::CalculateDamOpening()
{
    float waterLevel = this->jsonDoc["water_level"];
    return waterLevel < L2
               ? 0
           : waterLevel < L2 + DELTAL
               ? 20
           : waterLevel < L2 + DELTAL * 2
               ? 40
           : waterLevel < L2 + DELTAL * 3
               ? 60
           : waterLevel < L2 + DELTAL * 4
               ? 80
               : 100;
}