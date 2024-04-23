#include "Observer.h"

#include <algorithm>

namespace HomoGebra
{
template <class Observer>
void Observable<Observer>::Attach(Observer* observer)
{
  // Add observer to list
  observers_.push_back(observer);
}

template <class Observer>
void Observable<Observer>::Detach(const Observer* observer)
{
  // Remove observer from list
  observers_.remove_if([observer](const Observer* obs)
                       { return obs == observer; });
}

template <class Observer>
template <class Event>
void Observable<Observer>::Notify(const Event& event) const
{
  std::ranges::for_each(
      observers_, [&event](const auto& observer) { observer->Update(event); });
}

template <class Event>
void ObservableGeometricObject::Notify(const Event& event) const
{
  Observable::Notify(event);
}

template void ObservableGeometricObject::Notify<ObjectEvent::Moved>(
    const ObjectEvent::Moved& event) const;

template void
ObservableGeometricObject::Notify<ObjectEvent::GoingToBeDestroyed>(
    const ObjectEvent::GoingToBeDestroyed& event) const;

template void ObservableGeometricObject::Notify<ObjectEvent::Renamed>(
    const ObjectEvent::Renamed& event) const;

template <class Event>
void ObservablePlane::Notify(const Event& event) const
{
  Observable::Notify(event);
}

template void ObservablePlane::Notify<PlaneEvent::ObjectRemoved>(
    const PlaneEvent::ObjectRemoved& event) const;

template Observable<GeometricObjectObserver>;
template Observable<PlaneObserver>;
}  // namespace HomoGebra