#include "Arduino.h"
#include "AccelStepperJonas.h"


AccelStepperJonas::AccelStepperJonas(int stp, int dir, int ms1, int ms2, int en) {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(en, OUTPUT);
  _stp = stp;
  _dir = dir;
  _ms1 = ms1;
  _ms2 = ms2;
  _en = en;
  _stepNow = 0;
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
};

//Default microstep mode function
void AccelStepperJonas::StepDefault(int steps, bool counterclock)
{
  digitalWrite(_dir, counterclock); //Pull direction pin low to move "forward"
  for(int x= 1; x<steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(_stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(_stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
};


// 1/8th microstep foward mode function
void AccelStepperJonas::StepSmall(int steps, bool counterclock)
{
  digitalWrite(_dir, counterclock); //Pull direction pin low to move "forward"
  digitalWrite(_ms1, HIGH); //Pull MS1, and _ms2 high to set logic to 1/8th microstep resolution
  digitalWrite(_ms2, HIGH);
  for(int x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(_stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(_stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
};

//Reset Big Easy Driver pins to default states
void AccelStepperJonas::resetEDPins()
{
  digitalWrite(_stp, LOW);
  digitalWrite(_dir, LOW);
  digitalWrite(_ms1, LOW);
  digitalWrite(_ms2, LOW);
  digitalWrite(_en, HIGH);
  _stepNow = 0;
};

//Reset Big Easy Driver pins to default states
void AccelStepperJonas::resetBEDPins()
{
  digitalWrite(_stp, LOW);
  digitalWrite(_dir, LOW);
  digitalWrite(_ms1, LOW);
  digitalWrite(_ms2, LOW);
  digitalWrite(_en, HIGH);
  _stepNow = 0;
};

void AccelStepperJonas::StepMode(int mode, bool counterclock){
  resetEDPins();
  digitalWrite(_en, LOW);
  if(mode == 0){ //normal mode
    digitalWrite(_ms1, LOW); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
    digitalWrite(_ms2, LOW);
  }
  else if (mode == 1)
  {
     digitalWrite(_ms1, LOW); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
     digitalWrite(_ms2, HIGH);
  }

  digitalWrite(_dir, counterclock); //Pull direction pin low to move "forward"
};

void AccelStepperJonas::SetSteps(int steps){
  for(int y= 0; y<steps; y++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(_stp,HIGH); //Trigger one step forward
    delay(2);
    digitalWrite(_stp,LOW); //Pull step pin low so it can be triggered again
    delay(2);
  }
};

void AccelStepperJonas::SetStep(){
  digitalWrite(_stp,HIGH); //Trigger one step forward
  delay(1);
  digitalWrite(_stp,LOW); //Pull step pin low so it can be triggered again
  delay(1);
};

