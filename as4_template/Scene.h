/* Wes Rupert - wesrupert@outlook.com (wkr3)  *
 * Josh Braun - jxb532@case.edu (jxb532)      *
 * Case Western Reserve University - EECS 366 *
 * 10/07/2013 - Assignment 4                  */

#pragma once

#include "Object.h"

class Scene
{
public:
	void Load(char* file);
	Object* pObjectList;
	int ObjectCount;
};
