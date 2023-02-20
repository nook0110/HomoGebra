#include "GeometricObjectImplementation.h"

using namespace Event;

GeometricObjectImplementation::~GeometricObjectImplementation()
{}

void ObservableGeometricObject::Attach(std::shared_ptr<const ConstructionObserver> observer)
{
  observers_.push_back(observer);
}

void ObservableGeometricObject::Detach(const ConstructionObserver* observer)
{
  observers_.remove_if([observer](const std::shared_ptr<const ConstructionObserver>& ptr)
  {
    return ptr.get() == observer;
  });
}

void ObservableGeometricObject::Notify(Event::Moved) const
{
  // Update all observers
  for (const auto& observer : observers_)
    observer->Update(Event::Moved());
}

void ObservableGeometricObject::Notify(Event::Destroyed) const
{
  // Update all observers
  for (const auto& observer : observers_)
    observer->Update(Event::Destroyed());
}

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

void ConstructionPoint::Update(Event::Moved) const
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  object_.SetEquation(equation);
}

void ConstructionLine::Update(Event::Moved) const
{
  // Recalculate equation
  auto equation = RecalculateEquation();

  // Set new equation
  object_.SetEquation(equation);
}
