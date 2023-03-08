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
  equation *= transformation;
}

HomogeneousCoordinate& PointEquation::GetEquation()
{
  return equation;
}

const HomogeneousCoordinate& PointEquation::GetEquation() const
{
  return equation;
}

LineEquation::LineEquation(const HomogeneousCoordinate& equation)
{
}

void LineEquation::Apply(const Transformation& transformation)
{
  equation *= transformation.GetInverse().value();
}

void ConicEquation::Apply(const Transformation& transformation)
{
  auto inverse = transformation.GetInverse();
}