#pragma once

#include <Vector>

#include "stdafx.h"
#include "ControlPoint.h"

std::string serialize(std::vector<ControlPoint> list);
std::vector<QPoint> toQPoints(std::vector<ControlPoint> list);

QPoint toQPoint(ControlPoint point);
ControlPoint toControlPoint(QPoint point, double weight = 0.0);