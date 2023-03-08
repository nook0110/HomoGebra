#include "GeometricObjectFactory.h"
#include "Matrix.h"

PointFactory::PointFactory(Plane& plane)
  :plane_(plane)
{}

std::shared_ptr<Point> PointFactory::OnPlane(const PointEquation& coordinate)
{
  // Construct equation
  PointEquation equation(coordinate);

  // Create point
  auto point = std::make_shared<Point>(equation);

  // Add point to plane
  plane_.AddObject(point);

  // Return point
  return point;
}

LineFactory::LineFactory(Plane& plane)
  :plane_(plane)
{}

std::shared_ptr<Line> LineFactory::ByTwoPoints(const Point& first, const Point& second)
{
  // Construct equation

  // Calculate equation of a line that goes through 2 points
  // We need to solve the system of equations [matrix]:
  // f_ is first, s_ is second
  // | f_x f_y f_z | 0 |
  // | s_x s_y s_z | 0 |
  // |  1   1   1  | 1 |

  SquaredMatrix matrix(3);
  //matrix[0][0] = first.

  // Create equation
  LineEquation equation{ HomogeneousCoordinate{} };

  // Create line
  auto line = std::make_shared<Line>(equation);

  // Add line to plane
  plane_.AddObject(line);

  // Return line
  return line;
}