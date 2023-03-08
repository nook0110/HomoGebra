#include "GeometricObjectImplementation.h"

using namespace Event;

GeometricObjectImplementation::~GeometricObjectImplementation()
{}

void ObservableGeometricObject::Attach(const std::shared_ptr<ConstructionObserver>& observer)
{
  observers_.push_back(observer);
}

void ObservableGeometricObject::Detach(const ConstructionObserver* observer)
{
  observers_.remove_if([observer](const std::shared_ptr<ConstructionObserver>& ptr)
    {
      return ptr.get() == observer;
    });
}

void ObservableGeometricObject::Notify(const Event::Moved& moved) const
{
  // Update all observers
  for (const auto& observer : observers_)
    observer->Update(moved);
}

void ObservableGeometricObject::Notify(const Event::Destroyed& destroyed) const
{
  // Update all observers
  for (const auto& observer : observers_)
    observer->Update(destroyed);
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