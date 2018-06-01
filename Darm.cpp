/*
 * Darm.cpp
 *
 *  Created on: 24 apr. 2018
 *      Author: joeri
 */
#include "DArm.hpp"

DArm::DArm(double lengthN, double lengthF, Point A, Point B){
	this->lengthF = lengthF;
	this->lengthN = lengthN;
	this->A = A;
	this->B = B;
	this->stepAngle = 0.9;
	MotorA = AccelStepper(AccelStepper::DRIVER, 9, 8);
	MotorB = AccelStepper(AccelStepper::DRIVER, 7, 6);

	MotorA.setMaxSpeed(1000);
	MotorB.setMaxSpeed(1000);

	MotorA.setAcceleration(800);
	MotorB.setAcceleration(800);

	// set initial position
	Point start = Point{0, 200};
	Point angles = Convert(start);
	MotorA.setCurrentPosition(angles.x/stepAngle);
	MotorB.setCurrentPosition(angles.y/stepAngle);
}

Point DArm::Convert(Point point){
	//Serial.println("enter Convert()");
	Point ret;
	PointTuple intA;
	PointTuple intB;
	intA = CalcIntersects(this->A, this->lengthN, point, this->lengthF);
	intB = CalcIntersects(this->B, this->lengthN, point, this->lengthF);

	// determine correct ones
	// i'm thinking a is correct for A, b is correct for B?

	//calculate angle
	ret.x = atan(intA.a.y/intA.a.x) / 2 / PI * 360;
	ret.y = atan(intB.b.y/(intB.b.x - this->B.x)) / 2 / PI * 360;

	Serial.print("retx = ");
	Serial.print(ret.x, 3);
	Serial.print("rety = ");
	Serial.println(ret.y, 3);
	return ret;
}

PointTuple DArm::CalcIntersects(Point A, double Ar, Point B, double Br){
	// http://paulbourke.net/geometry/circlesphere/
	// X3 = X2 +/- h (Y1 - Y0)/d
	// 0 = base, 1 = point, 2 = centre, 3 = intersect
	// d = distance 0 - 1

	// calculate/ check d
	// d = ||P1 - P0||
	// if d > R0 + R1 => nope
	//Serial.println("Start Calcintersects()");
	//Serial.print("pointA ");
	//printPoint(A);
	//Serial.println("");
	//Serial.print("pointB ");
	//printPoint(B);
	//Serial.println("");
	//Serial.print("Ar ");
	//Serial.print(Ar, DEC);
	//Serial.print(", Br ");
	//Serial.print(Br, DEC);
	//Serial.println();
	double d = sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
	//Serial.print("d = ");
	//Serial.println(d, 3);
	if(d > (Ar + Br)){
		return PointTuple{Point{-1, -1}, Point{-1, -1}}; // ERROR
	}

	// a = (r0^2 - r1^2 + d^2 ) / (2 d)
	double a = (Ar*Ar - Br*Br + d*d) / (2 * d);
	//Serial.print("a = ");
	//Serial.println(a, 3);

	//h2 = r0^2 - a^2
	double h = sqrt(Ar*Ar - a*a);
	//Serial.print("h = ");
	//Serial.println(h, 3);

	// calculate XY2
	// P2 = P0 + a ( P1 - P0 ) / d
	Point C; // the centre point between A and B
	C.x = A.x + a*(B.x - A.x) / d;
	C.y = A.y + a*(B.y - A.y) / d;
	//Serial.print("C.x = ");
	//Serial.println(C.x, 3);
	//Serial.print("C.y = ");
	//Serial.println(C.y, 3);

	PointTuple R; // resulting tuple of points
	// X3 = X2 +/- h (Y1 - Y0)/d
	R.a.x = C.x + h*(B.y - A.y) / d;
	R.b.x = C.x - h*(B.y - A.y) / d;
	Serial.print("R.a.x = ");
	Serial.println(R.a.x, 3);
	Serial.print("R.b.x = ");
	Serial.println(R.b.x, 3);

	R.a.y = C.y - h*(B.x - A.x) / d;
	R.b.y = C.y + h*(B.x - A.x) / d;
	Serial.print("R.a.y = ");
	Serial.println(R.a.y, 3);
	Serial.print("R.b.y = ");
	Serial.println(R.b.y, 3);

	return R;
}

void DArm::MoveTo(Point point){
	// convert point to angles
	Point newAngles = Convert(point);
	Serial.println("starting moveTo");
	Serial.print("point: ");
	printPoint(point);
	Serial.println();
	Serial.print("angles:");
	printPoint(newAngles);
	Serial.println();

	// calculate what steps need to be taken
	int stepsA = (newAngles.x) / stepAngle;
	int stepsB = (newAngles.y) / stepAngle;
	Serial.print("steps: ");
	Serial.print(stepsA);
	Serial.print(", ");
	Serial.print(stepsB);
	Serial.println();
	Serial.println("steps calculated");

	// move steps
	MotorA.moveTo(stepsA);
	MotorB.moveTo(stepsB);
	Serial.println("steps set");
	MotorA.run();
	MotorB.run();
	Serial.println("running");
	while((MotorA.distanceToGo() + MotorB.distanceToGo()) > 0){
		Serial.print("steps to go A:");
		Serial.print(MotorA.distanceToGo(), DEC);
		Serial.print(", B: ");
		Serial.print(MotorB.distanceToGo(), DEC);
		Serial.println();
		MotorA.run();
		MotorB.run();
		// delay(1);
	}
	Serial.println("done");
}

void DArm::printPoint(Point p)
{
	Serial.print("{");
	Serial.print(p.x, 3);
	Serial.print(", ");
	Serial.print(p.y, 3);
	Serial.print("}");
}
