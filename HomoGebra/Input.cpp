#include "Input.h"

template <class GeometricObjectType>
NearbyObjectGetter<GeometricObjectType>::NearbyObjectGetter(
    Plane& plane, sf::RenderWindow& window, GeometricObjectType* last_object)
    : window_(window), last_object_(std::move(last_object)), finder_(plane)
{
  InitActionMap();
}

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
void NearbyObjectGetter<GeometricObjectType>::Update(const sf::Event& event)
{
  // Update the action map.
  action_map_.pushEvent(event);

  // Check if mouse was clicked
  if (action_map_.isActive(Action::kClick))
  {
    FindNearestObject();
  }

  // Clear last event
  action_map_.clearEvents();
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::InitActionMap()
{
  // Create the action map.
  action_map_[Action::kClick] =
      thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce);
}

template <class GeometricObjectType>
void NearbyObjectGetter<GeometricObjectType>::FindNearestObject()
{
  // Get coordinates of a mouse
  const auto mouse_position = sf::Mouse::getPosition(window_);

  // Convert mouse coordinates to world coordinates.
  const auto mouse_world_position = window_.mapPixelToCoords(mouse_position);

  // Find nearest object
  SetObject(
      finder_.GetNearestObject<GeometricObjectType>(mouse_world_position));
}

template class NearbyObjectGetter<GeometricObject>;
template class NearbyObjectGetter<Point>;
template class NearbyObjectGetter<Line>;
template class NearbyObjectGetter<Conic>;