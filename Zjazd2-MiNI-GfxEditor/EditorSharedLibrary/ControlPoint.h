#pragma once

#include <string>

#define CONTROL_POINT __declspec(dllexport)

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
}  // namespace esl
