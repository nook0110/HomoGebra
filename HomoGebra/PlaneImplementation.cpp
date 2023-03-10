#include "PlaneImplementation.h"

void PlaneImplementation::AddObject(
    const std::shared_ptr<GeometricObject>& object)
{
  // Add object to vector of all objects
  objects_.push_back(object);
}

void PlaneImplementation::RemoveObject(const GeometricObject* object)
{
  // Delete object from vector of all objects
  objects_.erase(
      std::remove_if(objects_.begin(), objects_.end(),
                     [object](const std::shared_ptr<GeometricObject>& obj)
                     { return obj.get() == object; }),
      objects_.end());
}

const std::vector<std::shared_ptr<GeometricObject>>&
PlaneImplementation::GetObjects() const
{
  // Return vector of all objects
  return objects_;
}