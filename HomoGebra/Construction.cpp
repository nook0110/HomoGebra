#include "Construction.h"
#include "Plane.h"

void ConstructionPoint::Update(const Event::Moved&) const
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  object_.SetEquation(equation);
}

void ConstructionPoint::Update(const Event::Destroyed& destroyed) const
{
  destroyed.plane_.DeletePoint(object_);
}

void ConstructionLine::Update(Event::Moved) const
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  object_.SetEquation(equation);
}

PointEquation ConstructionOnPlane::RecalculateEquation() const
{
  return object_.GetEquation();
}
