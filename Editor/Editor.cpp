// Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ControlPointList.h"


int main()
{
	printf(controlPointList.toString().c_str());

	controlPointList.List.push_back(ControlPoint(1L, 1L, 0.0));

	printf(controlPointList.toString().c_str());

    return 0;
}

