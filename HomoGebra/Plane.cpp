#include "Plane.h"

void Plane::AddObject(const std::shared_ptr<GeometricObject>& object)
{
  // Add object to plane
  implementation_.AddObject(object);
}

const std::vector<std::shared_ptr<GeometricObject>>& Plane::GetObjects() const
{
  // Return all objects
  return implementation_.GetObjects();
}