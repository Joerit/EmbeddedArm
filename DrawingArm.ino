#include "Arduino.h"
#include "DArm.hpp"
//The setup function is called once at startup of the sketch

DArm DA(133.0, 133.0, Point{0, 0}, Point{100, 0});
void setup()
{
	Serial.begin(115200);
	Serial.println("setup done");
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	while(!Serial.available()){
		Serial.print("in loop");
	}
	Serial.read();

	Serial.print("startpos: ");
	Serial.print(DA.MotorA.currentPosition());
	Serial.print(", ");
	Serial.print(DA.MotorA.currentPosition());
	Serial.println();
/*
	Serial.print("move to ");
	DA.printPoint({25, 200});
	DA.MoveTo({25, 200});
	Serial.print("move to ");
	DA.printPoint({50, 200});
	DA.MoveTo({50, 200});
	Serial.print("move to ");
	DA.printPoint({50, 225});
	DA.MoveTo({50, 225});
	Serial.print("move to ");
	DA.printPoint({25, 225});
	DA.MoveTo({25, 225});
*/
	Serial.print("move to ");
	DA.printPoint({0, 200});
	DA.MoveTo({0, 200});
	Serial.print("move to ");
	DA.printPoint({75, 200});
	DA.MoveTo({75, 200});



}

