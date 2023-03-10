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
  // Check if destroyed object is point that we contain
  if (destroyed.object == point_.get())
  {
    // Realese the ownership
    point_.reset();
    return;
  }

  // Destroy the point
  point_->Destroy(destroyed.plane);
}

const PointEquation& ConstructionPoint::GetEquation() const
{
  // Return point equation
  return point_->GetEquation();
}

void ConstructionPoint::SetEquation(const PointEquation& equation)
{
  // Set new equation
  point_->SetEquation(equation);
}

PointEquation ConstructionOnPlane::RecalculateEquation() const
{
  return GetEquation();
}

void ConstructionLine::Update(const Event::Moved&)
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  SetEquation(equation);
}

void ConstructionLine::Update(const Event::Destroyed& destroyed)
{
  // Check if destroyed object is line that we contain
  if (destroyed.object == line_.get())
  {
    // Realese the ownership
    line_.reset();
    return;
  }

  // Destroy the line
  line_->Destroy(destroyed.plane);
}

void ConstructionLine::SetEquation(const LineEquation& equation)
{
  // Set new equation
  line_->SetEquation(equation);
}