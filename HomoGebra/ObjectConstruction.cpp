#include "ObjectConstruction.h"

#include <random>
#include <utility>

#include "Assert.h"
#include "GeometricObject.h"
#include "Matrix.h"

namespace HomoGebra
{
GeometricObject* ConstructionPoint::GetObject() const { return GetPoint(); }

Point* ConstructionPoint::GetPoint() const
{
  // Return point
  return point_.get();
}
void ConstructionPoint::Update(const ObjectEvent::GoingToBeDestroyed& event)
{
  // Check if event object is point that we contain
  if (event.object == GetObject())
  {
    point_.reset();
    return;
  }

  // Destroy the point
  point_->AlertDestruction();
}

void ConstructionPoint::Update(const ObjectEvent::Renamed& renamed_event)
{
  // Renaming has no effect on object
}

const PointEquation& ConstructionPoint::GetEquation() const
{
  // Return point equation
  return point_->GetEquation();
}

void ConstructionPoint::SetEquation(PointEquation equation) const
{
  // Set new equation
  point_->SetEquation(std::move(equation));
}

PointOnPlane::PointOnPlane(PointEquation equation)
    : ConstructionPoint(), equation_(std::move(equation))
{
  // Set equation
  PointOnPlane::RecalculateEquation();
}

void PointOnPlane::RecalculateEquation()
{
  // Set equation
  SetEquation(equation_);
}

GeometricObject* ConstructionLine::GetObject() const
{
  // Return line
  return GetLine();
}

Line* ConstructionLine::GetLine() const
{
  // Return line
  return line_.get();
}

void ConstructionLine::Update(const ObjectEvent::GoingToBeDestroyed& event)
{
  // Check if event object is line that we contain
  if (event.object == GetObject())
  {
    // Destroy the line
    line_.reset();
    return;
  }

  // Destroy the line
  line_->AlertDestruction();
}

void ConstructionLine::Update(const ObjectEvent::Renamed& event) {}

const LineEquation& ConstructionLine::GetEquation() const
{
  // Return line equation
  return line_->GetEquation();
}

void ConstructionLine::SetEquation(const LineEquation& equation) const
{
  // Set new equation
  line_->SetEquation(equation);
}

LineOnPlane::LineOnPlane(LineEquation equation) : equation_(std::move(equation))
{
  // Set equation
  LineOnPlane::RecalculateEquation();
}

void LineOnPlane::RecalculateEquation()
{
  // Set equation
  SetEquation(equation_);
}

ByTwoPoints::ByTwoPoints(Point* first_point, Point* second_point)
    : first_point_(first_point), second_point_(second_point)
{
  // Attach to points
  first_point_->Attach(this);
  second_point_->Attach(this);

  // Recalculate equation
  RecalculateEquation();
}

ByTwoPoints::~ByTwoPoints()
{
  // Detach from points
  first_point_->Detach(this);
  second_point_->Detach(this);
}

void ByTwoPoints::RecalculateEquation()
{
  // Construct equation

  // Calculate equation of a line that goes through 2 points
  // We need to solve the system of equations [matrix]:
  // f_ is first, s_ is second
  // and r is random numbers
  // | f_x f_y f_z | 0 |
  // | s_x s_y s_z | 0 |
  // |  r   r   r  | 1 |

  // Get equations of points
  const auto& f_equation = first_point_->GetEquation().GetEquation();
  const auto& s_equation = second_point_->GetEquation().GetEquation();

  // Create matrix
  HomoGebra::ComplexSquaredMatrix matrix{3};

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

  // Set random number generator
  constexpr long double kLowerBound = -10000;
  constexpr long double kUpperBound = 10000;
  std::uniform_real_distribution<double> uniform_real_distribution(kLowerBound,
                                                                   kUpperBound);
  std::default_random_engine default_random_engine;

  // Set third row
  std::ranges::for_each(
      third_row,
      [&uniform_real_distribution, &default_random_engine](Complex& value)
      {
        value = Complex{uniform_real_distribution(default_random_engine),
                        uniform_real_distribution(default_random_engine)};
      });

  // Get augmentation
  auto& augmentation = matrix.GetAugmentation();

  // Set augmentation
  std::fill(augmentation.begin(), std::prev(augmentation.end()), Complex{0});
  augmentation.back() = Complex{1};

  // Get solution
  const auto solution = matrix.GetSolution();

  // Check if solution exists
  Assert(solution.has_value(), "Matrix has no solution!");

  // Get value
  const auto& value = *solution;

  // Create equation
  SetEquation(LineEquation({value[0], value[1], value[2]}));
}

GeometricObject* ConstructionConic::GetObject() const
{
  // Return conic
  return GetConic();
}

Conic* ConstructionConic::GetConic() const
{
  // Return conic
  return conic_.get();
}

void ConstructionConic::Update(const ObjectEvent::GoingToBeDestroyed& event)
{
  // Check if event object is line that we are containing
  if (event.object == GetObject())
  {
    conic_.reset();
    return;
  }

  // Destroy the conic
  conic_->AlertDestruction();
}

void ConstructionConic::Update(const ObjectEvent::Renamed& event) {}

ConicOnPlane::ConicOnPlane(ConicEquation equation)
    : equation_(std::move(equation))
{
  ConicOnPlane::RecalculateEquation();
}

void ConicOnPlane::RecalculateEquation() { SetEquation(equation_); }

void ConstructionConic::SetEquation(ConicEquation equation) const
{
  conic_->SetEquation(std::move(equation));
}
}  // namespace HomoGebra