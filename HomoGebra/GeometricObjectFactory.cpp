#include "GeometricObjectFactory.h"

#include <cassert>

#include "Matrix.h"

PointFactory::PointFactory(Plane& plane) : plane_(plane) {}

Point* PointFactory::OnPlane(const PointEquation& coordinate)
{
  // Construct equation
  PointEquation equation(coordinate);

  // Create point
  auto point = std::make_unique<Point>(equation);

  auto point_ptr = point.get();

  // Add point to plane
  plane_.AddObject(std::move(point));

  const auto& name_generator = plane_.GetNameGenerator();

  // Rename point
  point_ptr->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return point
  return point_ptr;
}

Point* PointFactory::Projection(const Point& from, const Line& to)
{
  return nullptr;
}

LineFactory::LineFactory(Plane& plane) : plane_(plane) {}

Line* LineFactory::ByTwoPoints(const Point& first, const Point& second)
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
  for (size_t column = 0; column < first_row.size(); ++column)
  {
    first_row[column] = f_equation[static_cast<Var>(column)];
  }

  // Get second row
  auto& second_row = matrix[1];

  // Set second row
  for (size_t column = 0; column < second_row.size(); ++column)
  {
    second_row[column] = s_equation[static_cast<Var>(column)];
  }

  // Get third row
  auto& third_row = matrix[2];

  // Set third row
  std::fill(third_row.begin(), third_row.end(), Complex{1});

  // Get augmentation
  auto& augmentation = matrix.GetAugmentation();

  // Set augmentation
  std::fill(augmentation.begin(), std::prev(augmentation.end()), Complex{0});
  augmentation.back() = Complex{1};

  // Get solution
  const auto solution = matrix.GetSolution();

  // Check if solution exists
  assert((solution.has_value()));

  // Get value
  const auto& value = *solution;

  // Create equation
  LineEquation equation{{value[0], value[1], value[2]}};

  // Create line
  auto line = std::make_unique<Line>(equation);

  // Add line to plane
  plane_.AddObject(std::move(line));

  // Return line
  return nullptr;
}

ConicFactory::ConicFactory(Plane& plane) : plane_(plane) {}

Conic* ConicFactory::ByFivePoints(const Point& first, const Point& second,
                                  const Point& third, const Point& fourth,
                                  const Point& fifth)
{
  return nullptr;
}