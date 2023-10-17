#ifndef __TASK__
#define __TASK__

class Task {
private:
  int period;
  int timeElapsed;
  bool active;
  
public:
  virtual void Init(int period){
    this->active = false;
    this->period = period;  
    timeElapsed = 0;
  }

  virtual void Tick() = 0;

  bool UpdateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= period){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool IsActive(){
    return active;
  }

  void SetActive(bool active){
    this->active = active;
  }

  int GetPeriod(){
    return this->period;
  }
};

#endif
