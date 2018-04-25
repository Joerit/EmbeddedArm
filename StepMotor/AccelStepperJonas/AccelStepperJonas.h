/*
  AccelStepperJonas_h library voor de stepper easy driver
*/
#ifndef AccelStepperJonas_h
#define AccelStepperJonas_h

#include "Arduino.h"

class AccelStepperJonas{
  public:
    AccelStepperJonas(int stp, int dir, int ms1, int ms2, int en);
    void StepDefault(int, bool);
    void StepSmall(int, bool);
    void StepMode(int, bool);
    void SetSteps(int);
    void SetStep();
    void resetEDPins();
    
  private:
    int _stp;
    int _dir;
    int _ms1;
    int _ms2;
    int _en;
  	int _stepNow;
    void resetBEDPins();
};   

#endif
