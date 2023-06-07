#include "GeometricObjectImplementation.h"

#include <utility>

PointImplementation::PointImplementation(PointEquation equation)
    : equation_(std::move(equation))
{}

void PointImplementation::SetEquation(PointEquation equation)
{
  // Set equation
  equation_ = std::move(equation);

  // Notify observers
  Notify(Event::Moved());
}

const PointEquation& PointImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}

LineImplementation::LineImplementation(LineEquation equation)
    : equation_(std::move(equation))
{}

void LineImplementation::SetEquation(LineEquation equation)
{
  // Set equation
  equation_ = std::move(equation);

  // Notify observers
  Notify(Event::Moved());
}

const LineEquation& LineImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}

ConicImplementation::ConicImplementation(ConicEquation equation)
    : equation_(std::move(equation))
{}

void ConicImplementation::SetEquation(ConicEquation equation)
{
  // Set equation
  equation_ = std::move(equation);

  // Notify observers
  Notify(Event::Moved());
}

const ConicEquation& ConicImplementation::GetEquation() const
{
  // Return equation
  return equation_;
}