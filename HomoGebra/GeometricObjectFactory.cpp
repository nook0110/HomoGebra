#include "GeometricObjectFactory.h"
#include "Matrix.h"

PointFactory::PointFactory(Plane& plane)
  :plane_(plane)
{}

Point& PointFactory::OnPlane(const PointEquation & coordinate)
{
  // Construct equation
  PointEquation equation(coordinate);

  // Emplace new point
  return plane_.EmplacePoint(equation);
}

LineFactory::LineFactory(Plane& plane)
  :plane_(plane)
{}

Line& LineFactory::ByTwoPoints(const Point& first, const Point& second)
{
  // Construct equation
  
  // Calculate equation of a line that goes through 2 points
  // We need to solve the system of equations [matrix]:
  // f_ is first, s_ is second
  // | f_x f_y f_z | 0 |
  // | s_x s_y s_z | 0 |
  // |  1   1   1  | 1 |

  SquaredMatrix matrix(3);
  matrix[0][0] = first.


  // Emplace new line
  return plane_.EmplaceLine(equation);
}
