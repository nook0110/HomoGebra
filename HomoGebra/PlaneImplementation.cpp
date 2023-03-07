#include "PlaneImplementation.h"

void PlaneImplementation::DeletePoint(const Point& point)
{
  // Delete point from vector of all points
  points_.erase(std::remove(points_.begin(), points_.end(), point), points_.end());
}

void PlaneImplementation::DeleteLine(const Line& line)
{
  // Delete line from vector of all lines
  lines_.erase(std::remove(lines_.begin(), lines_.end(), line), lines_.end());
}

void PlaneImplementation::DeleteConic(const Conic& conic)
{
  // Delete conic from vector of all conics
  conics_.erase(std::remove(conics_.begin(), conics_.end(), conic), conics_.end());
}

Point& PlaneImplementation::EmplacePoint(const PointEquation& equation)
{
  // Emplace back the new point into vector of all points
  return points_.emplace_back(equation);
}

Line& PlaneImplementation::EmplaceLine(const LineEquation& equation)
{
  // Emplace back the new line into vector of all lines
  return lines_.emplace_back(equation);
}

Conic& PlaneImplementation::EmplaceConic(const ConicEquation& equation)
{
  // Emplace back the new conic into vector of all conics
  return conics_.emplace_back(equation);
}
