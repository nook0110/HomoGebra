#include "Equation.h"

#include <cassert>

const std::array<Var, 3> ConicEquation::kPrev = {Var::kZ, Var::kX, Var::kY};

const std::array<Var, 3> ConicEquation::kNext = {Var::kY, Var::kZ, Var::kX};

PointEquation::PointEquation(const HomogeneousCoordinate& _equation)
    : equation(_equation)
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

LineEquation::LineEquation(const HomogeneousCoordinate& _equation)
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
  assert(false);

  // TODO: Implement this function
}