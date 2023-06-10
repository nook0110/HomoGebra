#include "ObjectConstruction.h"

#include <cassert>
#include <utility>

#include "Matrix.h"

GeometricObject* ConstructionPoint::GetObject() const { return GetPoint(); }

Point* ConstructionPoint::GetPoint() const
{
  // Return point
  return point_.get();
}
void ConstructionPoint::Update(const Event::Destroyed& event)
{
  // Check if event object is point that we contain
  if (event.object == GetObject())
  {
    point_.reset();
    return;
  }

  // Destroy the point
  point_->Destroy();
}

void ConstructionPoint::Update(const Event::Renamed& event) {}

ConstructionPoint::ConstructionPoint() : point_(std::make_unique<Point>()) {}

const PointEquation& ConstructionPoint::GetEquation() const
{
  // Return point equation
  return point_->GetEquation();
}

void ConstructionPoint::SetEquation(PointEquation equation)
{
  // Set new equation
  point_->SetEquation(std::move(equation));
}

PointOnPlane::PointOnPlane(PointEquation equation)
    : equation_(std::move(equation))
{
  // Set equation
  PointOnPlane::RecalculateEquation();
}

void PointOnPlane::RecalculateEquation() { SetEquation(equation_); }

GeometricObject* ConstructionLine::GetObject() const { return GetLine(); }

Line* ConstructionLine::GetLine() const
{
  // Return line
  return line_.get();
}

void ConstructionLine::Update(const Event::Destroyed& event)
{
  // Check if event object is line that we contain
  if (event.object == GetObject())
  {
    line_.reset();
    return;
  }

  // Destroy the line
  line_->Destroy();
}

void ConstructionLine::Update(const Event::Renamed& event) {}

inline ConstructionLine::ConstructionLine() : line_(std::make_unique<Line>()) {}

const LineEquation& ConstructionLine::GetEquation() const
{
  // Return line equation
  return line_->GetEquation();
}

void ConstructionLine::SetEquation(const LineEquation& equation)
{
  // Set new equation
  line_->SetEquation(equation);
}

ByTwoPoints::ByTwoPoints(Point* first_point, Point* second_point)
    : first_point_(first_point), second_point_(second_point)
{}

void ByTwoPoints::RecalculateEquation()
{
  // Construct equation

  // Calculate equation of a line that goes through 2 points
  // We need to solve the system of equations [matrix]:
  // f_ is first, s_ is second
  // | f_x f_y f_z | 0 |
  // | s_x s_y s_z | 0 |
  // |  1   1   1  | 1 |

  // Get equations of points
  const auto& f_equation = first_point_->GetEquation().GetEquation();
  const auto& s_equation = second_point_->GetEquation().GetEquation();

  // Create matrix
  ComplexSquaredMatrix matrix{3};

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
  SetEquation(LineEquation({value[0], value[1], value[2]}));
}

GeometricObject* ConstructionConic::GetObject() const { return GetConic(); }

Conic* ConstructionConic::GetConic() const { return conic_.get(); }

void ConstructionConic::Update(const Event::Destroyed& event)
{
  // Check if event object is line that we are containing
  if (event.object == GetObject())
  {
    conic_.reset();
    return;
  }

  // Destroy the conic
  conic_->Destroy();
}

void ConstructionConic::Update(const Event::Renamed& event) {}

ConstructionConic::ConstructionConic() : conic_(std::make_unique<Conic>()) {}

ConicOnPlane::ConicOnPlane(ConicEquation equation)
    : equation_(std::move(equation))
{
  ConicOnPlane::RecalculateEquation();
}

void ConicOnPlane::RecalculateEquation() { SetEquation(equation_); }

void ConstructionConic::SetEquation(ConicEquation equation)
{
  conic_->SetEquation(std::move(equation));
}