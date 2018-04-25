/*
 * DArm.hpp
 *
 *  Created on: 24 apr. 2018
 *      Author: joeri
 */

#ifndef DARM_HPP_
#define DARM_HPP_

#include <math.h>
#include "Arduino.h"

struct Point{
	double x;
	double y;
};

struct PointTuple{
	Point a;
	Point b;
};

class DArm{
public:
	Point A;
	Point B;
	double lengthN;
	double lengthF;

	//constructor
	// lenthN: length of nearest part of arm, lengthF: length of furthest part of arm
	// A: x,y of left motor, B: x,y of right motor
	DArm(double lengthN, double lengthF, Point A, Point B);

	Point Convert(Point point);
	PointTuple CalcIntersects(Point A, double Ar, Point B, double Br);
};



#endif /* DARM_HPP_ */
