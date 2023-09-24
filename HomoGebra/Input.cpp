#include "Input.h"

#include "GeometricObject.h"

template <class GeometricObjectType>
NearbyObjectGetter<GeometricObjectType>::NearbyObjectGetter(
    Plane* plane, GeometricObjectType* last_object)
    : last_object_(std::move(last_object)), finder_(plane)
{}

template <class GeometricObjectType>
GeometricObjectType* NearbyObjectGetter<GeometricObjectType>::GetLastObject()
{
  return last_object_;
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::Reset()
{
  SetObject(nullptr);
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::SetObject(
    GeometricObjectType* object)
{
  last_object_ = object;
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::Update(
    const UserEvent::Click& event)
{
  FindNearestObject(event.position);
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::FindNearestObject(
    const sf::Vector2f& position)
{
  // Find nearest object
  SetObject(finder_.GetNearestObject<GeometricObjectType>(position));
}

template class NearbyObjectGetter<GeometricObject>;
template class NearbyObjectGetter<Point>;
template class NearbyObjectGetter<Line>;
template class NearbyObjectGetter<Conic>;