#include "PlaneImplementation.h"

void PlaneImplementation::AddObject(const std::shared_ptr<GeometricObject>& object)
{
  // Add object to vector of all objects
  objects_.push_back(object);
}

void PlaneImplementation::RemoveObject(GeometricObject* object)
{
  // Delete object from vector of all objects
  objects_.erase(
    std::remove_if(objects_.begin(), objects_.end(),
      [object](const std::shared_ptr<GeometricObject>& obj)
      {
        return obj.get() == object;
      }
    ),
    objects_.end());
}