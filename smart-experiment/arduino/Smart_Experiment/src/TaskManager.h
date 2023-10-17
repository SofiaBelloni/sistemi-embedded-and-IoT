#ifndef __TASK_MANAGER__
#define __TASK_MANAGER__

#include "Arduino.h"
#include "Task.h"
#include "Vector.h"
#include "Scheduler.h"

class TaskManager {
private:
    struct taskStruct
    {
        String name;
        Task* task;
    };
    taskStruct storage_array[10];
    Scheduler* scheduler;
    Vector<taskStruct> tasks;
    static TaskManager* instance;
    TaskManager();
    int CalculateMCD(int a, int b);
public:
    void AddTask(String name, Task* task);
    void RemoveTask(String name);
    Task* GetTask(String name);
    void SetTaskActive(String name, bool isActive);
    void SetScheduler(Scheduler* scheduler){this->scheduler = scheduler;}
    void ResetSchedulerBasePeriod(int newPeriod);
    void InitScheduler(Vector<int>* periods);
    static TaskManager* GetSingletonInstance();
};

#endif

