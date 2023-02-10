#pragma once
#include <vector>

#include "GeometricObject.h"

class Plane
{
public:

private:
  // All objects
  std::vector<Point> points_;
  std::vector<Line> lines_;
  std::vector<Conic> conics_;
};
