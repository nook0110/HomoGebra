#include "GeometricObjectImplementation.h"

PointImplementation::PointImplementation(const PointEquation& equation)
    : equation_(equation)
{}

void PointImplementation::SetEquation(const PointEquation& equation)
{
  // Set equation
  equation_ = equation;

  // Notify observers
  Notify(Event::Moved());
}

const PointEquation& PointImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}

LineImplementation::LineImplementation(const LineEquation& equation)
    : equation_(equation)
{}

void LineImplementation::SetEquation(const LineEquation& equation)
{
  // Set equation
  equation_ = equation;

  // Notify observers
  Notify(Event::Moved());
}

const LineEquation& LineImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}

ConicImplementation::ConicImplementation(const ConicEquation& equation)
    : equation_(equation)
{}

void ConicImplementation::SetEquation(const ConicEquation& equation)
{
  // Set equation
  equation_ = equation;

  // Notify observers
  Notify(Event::Moved());
}

const ConicEquation& ConicImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}