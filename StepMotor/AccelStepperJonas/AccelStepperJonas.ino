#include "AccelStepperJonas.h"

AccelStepperJonas stepper1(2,3,4,5,6);
AccelStepperJonas stepper2(7,8,9,10,11);

int steps = 50;
char user_input;

void setup(){
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
}

void loop(){
     while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      int steps = Serial.parseInt();
      Serial.println(steps);
      if(user_input =='1')
      {
        SmallStepMode(steps, false);
      }
      else if(user_input =='2')
      {
        SmallStepMode(steps, true);
      }
      else if(user_input =='3')
      {
        stepper1.StepMode(1, true);
        for(int x= 1; x<steps; x++)  //Loop the forward stepping enough times for motion to be visible
        {
          stepper1.SetStep();
        }
        Serial.println("Enter new option");
        Serial.println();
        stepper1.resetEDPins();
      }
      else if(user_input =='4')
      {
        stepper2.StepMode(1, true);
        for(int x= 1; x<steps; x++)  //Loop the forward stepping enough times for motion to be visible
        {
          stepper2.SetStep();
        }
        Serial.println("Enter new option");
        Serial.println();
        stepper2.resetEDPins();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
    }
}

void SmallStepMode(int steps, bool counterclock)
{
  Serial.println("Stepping at 1/8th microstep mode.");
  stepper1.StepMode(0, counterclock);
  stepper2.StepMode(0, not(counterclock));
  for(int x= 0; x<steps; x+=2)  //Loop the forward stepping enough times for motion to be visible
  {
    stepper1.SetSteps(2);
    delay(5);
    stepper2.SetSteps(2);
    delay(5);
  }
  Serial.println("Enter new option");
  Serial.println();
  stepper1.resetEDPins();
  stepper2.resetEDPins();
}
