#include "ObjectProvider.h"

#include "GeometricObject.h"

namespace HomoGebra
{
ObjectProvider::ObjectProvider(Plane* plane) : plane_(plane) {}

template <class GeometricObjectType>
GeometricObjectType* ObjectProvider::GetNearestObject(
    const sf::Vector2f& position, const Distance max_distance)
{
  // Get all GeometricObjectType objects
  auto objects = plane_->GetObjects<GeometricObjectType>();

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

template GeometricObject* ObjectProvider::GetNearestObject(
    const sf::Vector2f& position, Distance max_distance);
template Point* ObjectProvider::GetNearestObject(const sf::Vector2f& position,
                                                 Distance max_distance);
template Line* ObjectProvider::GetNearestObject(const sf::Vector2f& position,
                                                Distance max_distance);
template Conic* ObjectProvider::GetNearestObject(const sf::Vector2f& position,
                                                 Distance max_distance);
}  // namespace HomoGebra