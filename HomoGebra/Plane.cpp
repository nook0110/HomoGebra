#include "Plane.h"

Point& Plane::EmplacePoint(const PointEquation& equation)
{
  // Emplace new point
  return implementation_.EmplacePoint(equation);
}

Line& Plane::EmplaceLine(const LineEquation& equation)
{
  // Emplace new line
  return implementation_.EmplaceLine(equation);
}

Conic& Plane::EmplaceConic(const ConicEquation& equation)
{
  // Emplace new conic
  return implementation_.EmplaceConic(equation);
}

void Plane::DestroyPoint(const Point& point)
{
  implementation_.DeletePoint(point);
}

void Plane::DestroyLine(const Line& line)
{
  implementation_.DeleteLine(line);
}

void Plane::DestroyConic(const Conic& conic)
{
  implementation_.DeleteConic(conic);
}
