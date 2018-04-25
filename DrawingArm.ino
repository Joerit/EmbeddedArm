#include "Arduino.h"
#include "DArm.hpp"
//The setup function is called once at startup of the sketch


void setup()
{
	Serial.begin(9600);
	Serial.println("setup done");
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	DArm DA(133.0, 133.0, Point{0, 0}, Point{100, 0});

	Serial.println("point {56, 165} from A: ");
	PointTuple PT = DA.CalcIntersects(DA.A, DA.lengthN, Point{56, 165}, DA.lengthF);
	Serial.print("{");
	printPoint(PT.a);
	Serial.print(", ");
	printPoint(PT.b);
	Serial.print("}}");
	Serial.println("");

	Serial.println("point {56, 165} from B: ");
	PT = DA.CalcIntersects(DA.B, DA.lengthN, Point{56, 165}, DA.lengthF);
	Serial.print("{");
	printPoint(PT.a);
	Serial.print(", ");
	printPoint(PT.b);
	Serial.print("}}");
	Serial.println("");

	Point angles = DA.Convert(Point{56, 165});
	Serial.println("angles:");
	printPoint(angles);
	Serial.println("");
	while(true);
//Add your repeated code here
}
void printPoint(Point p)
{
	Serial.print("{");
	Serial.print(p.x, 3);
	Serial.print(", ");
	Serial.print(p.y, 3);
	Serial.print("}");
}

