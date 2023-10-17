#include "ExperimentTask.h"
#include "Config.h"
#include "ServoMotorImpl.h"
#include "SonarImpl.h"
#include "MsgService.h"
#include "StartButtonTask.h"
#include "StopButtonTask.h"
#include "TaskManager.h"
#include "Potentiometer.h"

ExperimentTask::ExperimentTask(int sonarTrigPin, int sonarEchoPin, int servoPin, float temperature){
    this->experimentState = INIT;
    this->experiment = new Experiment(sonarTrigPin, sonarEchoPin, servoPin, temperature);
    this->errorTimeCounter = 0;
}

ExperimentTask::state ExperimentTask::GetExperimentState(){
    return this->experimentState;
}

void ExperimentTask::Tick(){
    switch (this->experimentState)
    {
    case INIT:
        this->InitState();
        break;
    case STARTED:
        this->StartedState();
        break;
    case ENDED:
        this->EndedState();
        break;
    case ERROR:
        this->ErrorState();
        break;
    default:
        break;
    }
}

void ExperimentTask::InitState(){
    if (((StartButtonTask*)TaskManager::GetSingletonInstance()->GetTask(START_BUTTON_TASK))->IsBtnPressed())
    {
        if (this->experiment->isObjectDetected())
        {
            this->experimentState = STARTED;
            this->Init(Potentiometer::GetSingletonInstance()->GetValue());
            this->SetActive(true);
            TaskManager::GetSingletonInstance()->ResetSchedulerBasePeriod(Potentiometer::GetSingletonInstance()->GetValue());
            MsgService::GetSingletonInstance()->Start();
            this->experiment->ResetExperiment();
            this->experiment->GetServo()->On();
        }else
        {
            this->experimentState = ERROR;
            MsgService::GetSingletonInstance()->Error();
            this->errorTimeCounter = millis()/1000;
        }
    }
}

void ExperimentTask::StartedState(){
    if (((StopButtonTask*)TaskManager::GetSingletonInstance()->GetTask(STOP_BUTTON_TASK))->IsBtnPressed()
    || this->experiment->GetTime() >= MAX_TIME)
    {
        this->experimentState = ENDED;
        MsgService::GetSingletonInstance()->End();
        this->experiment->GetServo()->Off();
    } else if (this->experiment->GetTime() < MAX_TIME)
    {
        this->experiment->UpdateValues();
        MsgService::GetSingletonInstance()->SendPositionValue(
            //If the position is -1 it mean that the objet is not detected. so we send 0 to the viewer
            this->experiment->GetPosition()==-1 ? 0 : this->experiment->GetPosition(), this->experiment->GetTime());
        MsgService::GetSingletonInstance()->SendSpeedValue(
            this->experiment->GetSpeed(), this->experiment->GetTime());
        MsgService::GetSingletonInstance()->SendAccelerationValue(
            this->experiment->GetAcceleration(), this->experiment->GetTime());
        }
}

void ExperimentTask::EndedState(){
    if (MsgService::GetSingletonInstance()->ConfirmationReceived())
    {
        this->experimentState = INIT;
        MsgService::GetSingletonInstance()->Wait();
    }
}

void ExperimentTask::ErrorState(){
    if ((millis()/1000)-errorTimeCounter >= ERROR_TIME)
    {
        this->experimentState = INIT;
        MsgService::GetSingletonInstance()->Wait();
    }
    
}
