#pragma once

#include <List>

#include "ControlPoint.h"

std::string serialize(std::list<ControlPoint> list);

// globally accessible control point list
static std::list<ControlPoint> controlPointList;