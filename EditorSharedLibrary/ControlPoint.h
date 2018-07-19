#pragma once

#include <string>

#ifdef ESL_EXPORTS
#define CONTROL_POINT __declspec(dllexport)
#else
#define CONTROL_POINT __declspec(dllimport)
#endif

namespace esl {
	class CONTROL_POINT ControlPoint {
	private:
		long _x;
		long _y;
		double _weight;

	public:
		ControlPoint(long x, long y, double weight);
		long getX();
		long getY();
		double getWeight();
		std::string toString();
	};
} // namespace esl