#include "GeometricObjectFactory.h"

#include "Matrix.h"

PointFactory::PointFactory(Plane& plane) : plane_(plane) {}

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

LineFactory::LineFactory(Plane& plane) : plane_(plane) {}

std::shared_ptr<Line> LineFactory::ByTwoPoints(const Point& first,
                                               const Point& second)
{
  // Construct equation

  // Calculate equation of a line that goes through 2 points
  // We need to solve the system of equations [matrix]:
  // f_ is first, s_ is second
  // | f_x f_y f_z | 0 |
  // | s_x s_y s_z | 0 |
  // |  1   1   1  | 1 |

  // Get equations of points
  const auto& f_equation = first.GetEquation().GetEquation();
  const auto& s_equation = second.GetEquation().GetEquation();

  // Create matrix
  SquaredMatrix matrix{3};

  // Get first row
  auto& first_row = matrix[0];

  // Set first row
  for (int column = 0; column < first_row.size(); ++column)
  {
    first_row[column] = f_equation[static_cast<var>(column)];
  }

  // Get second row
  auto& second_row = matrix[1];

  // Set second row
  for (int column = 0; column < second_row.size(); ++column)
  {
    second_row[column] = s_equation[static_cast<var>(column)];
  }

  // Get third row
  auto& third_row = matrix[2];

  // Set third row
  std::fill(third_row.begin(), third_row.end(), complex{1});

  // Get augmentation
  auto& augmentation = matrix.GetAugmentation();

  // Set augmentation
  std::fill(augmentation.begin(), std::prev(augmentation.end()), complex{0});
  augmentation.back() = complex{1};

  // Get solution
  auto solution = matrix.GetSolution();

  // Check if solution exists
  if (!solution)
  {
    throw std::runtime_error("Points are on the same line");
  }

  // Get value
  const auto& value = *solution;

  // Create equation
  LineEquation equation{{value[0], value[1], value[2]}};

  // Create line
  auto line = std::make_shared<Line>(equation);

  // Add line to plane
  plane_.AddObject(line);

  // Return line
  return line;
}

ConicFactory::ConicFactory(Plane& plane) : plane_(plane) {}