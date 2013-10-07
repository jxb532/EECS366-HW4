/* Wes Rupert - wesrupert@outlook.com (wkr3)  *
 * Josh Braun - jxb532@case.edu (jxb532)      *
 * Case Western Reserve University - EECS 366 *
 * 10/07/2013 - Assignment 4                  */

#pragma once

class Vertex
{
public:
	Vertex();
	Vertex(float _x, float _y, float _z);
	void Normalize();
	float x, y, z, h;
};