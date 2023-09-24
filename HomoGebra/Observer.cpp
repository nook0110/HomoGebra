#include "Observer.h"

void ObservableGeometricObject::Attach(GeometricObjectObserver* observer)
{
  // Add observer to list
  observers_.push_back(observer);
}

void ObservableGeometricObject::Detach(const GeometricObjectObserver* observer)
{
  // Remove observer from list
  observers_.remove_if([observer](const GeometricObjectObserver* obs)
                       { return obs == observer; });
}

template <class Event>
void ObservableGeometricObject::Notify(const Event& event) const
{
  for (const auto& observer : observers_) observer->Update(event);
}

template void ObservableGeometricObject::Notify<ObjectEvent::Moved>(
    const ObjectEvent::Moved& event) const;

template void ObservableGeometricObject::Notify<ObjectEvent::Destroyed>(
    const ObjectEvent::Destroyed& event) const;

template void ObservableGeometricObject::Notify<ObjectEvent::Renamed>(
    const ObjectEvent::Renamed& event) const;