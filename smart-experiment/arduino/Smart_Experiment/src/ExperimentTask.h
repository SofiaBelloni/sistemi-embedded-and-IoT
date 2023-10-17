#ifndef __EXPERIMENT_TASK__
#define __EXPERIMENT_TASK__

#include "Task.h"
#include "Experiment.h"

class ExperimentTask : public Task{
private:
    Experiment* experiment;
    int errorTimeCounter;
    void InitState();
    void StartedState();
    void EndedState();
    void ErrorState();
public:
    enum state {INIT, STARTED, ENDED, ERROR};
    state experimentState;
    ExperimentTask(int sonarTrigPin, int sonarEchoPin, int servoPin, float temperature);
    state GetExperimentState();
    void Tick();
};

#endif
