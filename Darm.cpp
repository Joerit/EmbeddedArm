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
	this->currentA = Point(45, 45);
	this->currentP = Point(0, 0);
	this->stepAngle = 0.9;
}

Point DArm::Convert(Point point){
	Point ret;
	PointTuple intA;
	PointTuple intB;
	intA = CalcIntersects(this->A, this->lengthN, point, this->lengthF);
	intB = CalcIntersects(this->B, this->lengthN, point, this->lengthF);

	// determine correct ones
	// i'm thinking a is correct for A, b is correct for B?
	ret.x = tanh(intA.a.y/intA.a.x) / 2 / PI * 360;
	ret.y = tanh(intB.b.y/(intB.b.x - this->B.x)) / 2 / PI * 360;
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

	double d = sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
	Serial.print("d = ");
	Serial.println(d, 3);
	if(d > (Ar + Br)){
		return PointTuple{Point{-1, -1}, Point{-1, -1}}; // ERROR
	}

	// a = (r0^2 - r1^2 + d^2 ) / (2 d)
	double a = (Ar*Ar - Br*Br + d*d) / (2 * d);
	Serial.print("a = ");
	Serial.println(a, 3);

	//h2 = r0^2 - a^2
	double h = sqrt(Ar*Ar - a*a);
	Serial.print("h = ");
	Serial.println(h, 3);

	// calculate XY2
	// P2 = P0 + a ( P1 - P0 ) / d
	Point C; // the centre point between A and B
	C.x = A.x + a*(B.x - A.x) / d;
	C.y = A.y + a*(B.y - A.y) / d;
	Serial.print("C.x = ");
	Serial.println(C.x, 3);
	Serial.print("C.y = ");
	Serial.println(C.y, 3);

	PointTuple R; // resulting tuple of points
	// X3 = X2 +/- h (Y1 - Y0)/d
	R.a.x = C.x + h*(B.y - A.y) / d;
	R.b.x = C.x - h*(B.y - A.y) / d;
	Serial.print("R.a.x = ");
	Serial.println(R.a.x, 3);
	Serial.print("R.b.x = ");
	Serial.println(R.b.x, 3);

	R.a.y = C.y + h*(B.x - A.x) / d;
	R.b.y = C.y - h*(B.x - A.x) / d;
	Serial.print("R.a.y = ");
	Serial.println(R.a.y, 3);
	Serial.print("R.b.y = ");
	Serial.println(R.b.y, 3);

	return R;
}

void DArm::MoveTo(Point point){
	// convert point to angles
	Point newAngles = Convert(point);

	// calculate what steps need to be taken
	int stepsA = (newAngles.x) / stepAngle;
	int stepsB = (newAngles.y) / stepAngle;

	// move steps

}
