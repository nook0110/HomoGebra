#include "ObjectConstruction.h"

void ConstructionPoint::Update(const Event::Moved&)
{
  // Recalculate equation
  const auto equation = RecalculateEquation();

  // Set new equation
  SetEquation(equation);
}

void ConstructionPoint::Update(const Event::Destroyed& event)
{
  // Check if event object is point that we contain
  if (event.object == point_.get())
  {
    // Release the ownership
    point_.reset();
    return;
  }

  // Destroy the point
  point_->Destroy(event.plane);
}

void ConstructionPoint::Update(const Event::Renamed& event) {}

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

ConstructionOnPlane::ConstructionOnPlane(const PointEquation& equation) {}

PointEquation ConstructionOnPlane::RecalculateEquation() const
{
  // Return point equation, because it has no dependencies
  return GetEquation();
}

void ConstructionLine::Update(const Event::Moved&)
{
  // Recalculate equation
  const auto equation = RecalculateEquation();

  // Set new equation
  SetEquation(equation);
}

void ConstructionLine::Update(const Event::Destroyed& event)
{
  // Check if event object is line that we contain
  if (event.object == line_.get())
  {
    // Release the ownership
    line_.reset();
    return;
  }

  // Destroy the line
  line_->Destroy(event.plane);
}

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