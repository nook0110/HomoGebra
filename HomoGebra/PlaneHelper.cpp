#include "PlaneHelper.h"

#include "GeometricObject.h"

PlaneHelper::PlaneHelper(Plane& plane) : plane_(plane) {}

template <class GeometricObjectType>
GeometricObjectType* PlaneHelper::GetNearestObject(const sf::Vector2f& position,
                                                   const float max_distance)
{
  // Get all GeometricObjectType objects
  auto objects = plane_.GetObjects<GeometricObjectType>();

  GeometricObjectType* nearest_object{nullptr};
  float current_distance = std::numeric_limits<float>::max();

  // Find nearest
  for (auto& object : objects)
  {
    // Get distance to object
    const auto distance = object->GetDistance(position);

    // Check if distance is less than current distance
    if (distance < current_distance)
    {
      // Update current distance
      current_distance = distance;

      // Update nearest object
      nearest_object = dynamic_cast<GeometricObjectType*>(object);
    }
  }

  // Check if distance is less than max distance
  if (current_distance < max_distance)
  {
    // Return nearest object
    return nearest_object;
  }

  // Else return nullptr
  return nullptr;
}

template GeometricObject* PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance);
template Point* PlaneHelper::GetNearestObject(const sf::Vector2f& position,
                                              const float max_distance);
template Line* PlaneHelper::GetNearestObject(const sf::Vector2f& position,
                                             const float max_distance);
template Conic* PlaneHelper::GetNearestObject(const sf::Vector2f& position,
                                              const float max_distance);