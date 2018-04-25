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
	Point A;			// coordinates of left motor axle
	Point B;			// coordinates of right motor axle
	double lengthN;		// length of nearest part of arm
	double lengthF;		// length of furthest part of arm
	double stepAngle;	// angle of one motor step

	//constructor
	// lenthN: length of nearest part of arm, lengthF: length of furthest part of arm
	// A: x,y of left motor, B: x,y of right motor
	DArm(double lengthN, double lengthF, Point A, Point B);

	// convert point to a set of angles
	Point Convert(Point point);

	// calculate intersecting points of circle radius Ar, centered at A,
	//	and circle radius Br, centered at B
	PointTuple CalcIntersects(Point A, double Ar, Point B, double Br);

	// move pen to coordinates point
	void MoveTo(Point point);
};



#endif /* DARM_HPP_ */
