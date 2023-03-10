#include "Equation.h"

const std::array<var, 3> ConicEquation::prev =
{ var::kZ, var::kX, var::kY };

const std::array<var, 3> ConicEquation::next =
{ var::kY, var::kZ,var::kX };

PointEquation::PointEquation(const HomogeneousCoordinate& _equation)
  :equation(_equation)
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
  :equation(_equation)
{}

void LineEquation::Apply(const Transformation& transformation)
{
  // Apply transformation to equation
  equation *= transformation.GetInverse().value();
}

void ConicEquation::Apply(const Transformation& transformation)
{
  /*
  * This function is not implemented yet, because it is not needed.
  */

  throw std::logic_error("The method or operation is not implemented.");

  // TODO: Implement this function
}