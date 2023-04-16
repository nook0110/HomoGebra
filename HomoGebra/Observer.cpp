#include "Observer.h"

using namespace Event;

void ObservableGeometricObject::Attach(
    const std::shared_ptr<GeometricObjectObserver>& observer)
{
  // Add observer to list
  observers_.push_back(observer);
}

void ObservableGeometricObject::Detach(const GeometricObjectObserver* observer)
{
  // Remove observer from list
  observers_.remove_if(
      [observer](const std::shared_ptr<GeometricObjectObserver>& ptr)
      { return ptr.get() == observer; });
}

void ObservableGeometricObject::Notify(const Event::Moved& moved) const
{
  // Update all observers
  for (const auto& observer : observers_) observer->Update(moved);
}

void ObservableGeometricObject::Notify(const Event::Destroyed& destroyed) const
{
  // Update all observers
  for (const auto& observer : observers_) observer->Update(destroyed);
}

void ObservableGeometricObject::Notify(
    const Event::Renamed& renamed_event) const
{
  // Update all observers
  for (const auto& observer : observers_) observer->Update(renamed_event);
}