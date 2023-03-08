#include "Construction.h"
#include "Plane.h"

void ConstructionPoint::Update(const Event::Moved&)
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  SetEquation(equation);
}

void ConstructionPoint::Update(const Event::Destroyed& destroyed)
{
}

const PointEquation& ConstructionPoint::GetEquation() const
{
  // Return point equation
  return point_->GetEquation();
}

void ConstructionPoint::SetEquation(const PointEquation& equation)
{
}

void ConstructionLine::Update(const Event::Moved&)
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  SetEquation(equation);
}

PointEquation ConstructionOnPlane::RecalculateEquation() const
{
  return GetEquation();
}

void ConstructionLine::SetEquation(const LineEquation& equation)
{
}