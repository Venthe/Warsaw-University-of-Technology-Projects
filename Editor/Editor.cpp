// Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ControlPointList.h"


int main()
{
	printf(serialize(controlPointList).c_str());

	controlPointList.push_back(ControlPoint(1L, 1L, 0.0));

	printf(serialize(controlPointList).c_str());

    return 0;
}

