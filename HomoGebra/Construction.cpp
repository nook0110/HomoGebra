#include "Construction.h"

void ConstructionPoint::Update(Event::Moved) const
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  object_.SetEquation(equation);
}

void ConstructionPoint::Update(Event::Destroyed) const
{
  object_.Destroy();
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
