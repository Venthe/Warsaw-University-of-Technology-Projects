#include "stdafx.h"
#include "ControlPoint.h"

namespace esl {
	inline ControlPoint::ControlPoint(long x, long y, double weight) {
		_x = x;
		_y = y;
		_weight = weight;
	}

	inline long ControlPoint::getX() {
		return _x;
	}

	inline long ControlPoint::getY() {
		return _y;
	}

	inline double ControlPoint::getWeight() {
		return _weight;
	}

	inline std::string ControlPoint::toString() {
		return std::to_string(_x) + " " + std::to_string(_y) + " " + std::to_string(_weight);
	}
} // namespace esl
