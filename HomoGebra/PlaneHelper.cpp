#include "PlaneHelper.h"

#include "GeometricObject.h"

PlaneHelper::PlaneHelper(Plane& plane) : plane_(plane) {}

template <class GeometricObjectType>
std::shared_ptr<GeometricObjectType> PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance)
{
  // Get all GeometricObjectType objects
  auto objects = plane_.GetObjects<GeometricObjectType>();

  std::shared_ptr<GeometricObjectType> nearest_object{nullptr};
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
      nearest_object = std::dynamic_pointer_cast<GeometricObjectType>(object);
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

template std::shared_ptr<GeometricObject> PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance);
template std::shared_ptr<Point> PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance);
template std::shared_ptr<Line> PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance);
template std::shared_ptr<Conic> PlaneHelper::GetNearestObject(
    const sf::Vector2f& position, const float max_distance);