#include "Equation.h"

#include "Assert.h"

PointEquation::PointEquation(HomogeneousCoordinate _equation)
    : equation(std::move(_equation))
{}

void PointEquation::Apply(const Transformation& transformation)
{
  // Apply transformation to equation
  equation *= transformation;
}

HomogeneousCoordinate& PointEquation::GetEquation()
{
  // Return equation
  return equation;
}

const HomogeneousCoordinate& PointEquation::GetEquation() const
{
  // Return equation
  return equation;
}

LineEquation::LineEquation(HomogeneousCoordinate _equation)
    : equation(_equation)
{}

void LineEquation::Apply(const Transformation& transformation)
{
  // Get inversion of transformation
  const auto inverse = transformation.GetInverse();

  // Check if it exists

  // Apply transformation to equation
  equation *= inverse.value();
}

void ConicEquation::Apply(const Transformation& transformation)
{
  /*
   * This function is not implemented yet, because it is not needed.
   */
  Assert(false, "Calling not implemented function!");

  // TODO: Implement this function
}