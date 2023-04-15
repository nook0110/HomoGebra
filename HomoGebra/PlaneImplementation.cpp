#include "PlaneImplementation.h"

#include <cassert>
#include <functional>

#include "GeometricObject.h"

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

bool PlaneImplementation::IsContained(const GeometricObject* object) const
{
  // Check if object is in vector of all objects
  return std::find_if(objects_.begin(), objects_.end(),
                      [object](const std::shared_ptr<GeometricObject>& obj)
                      { return obj.get() == object; }) != objects_.end();
}

const std::vector<std::shared_ptr<GeometricObject>>&
PlaneImplementation::GetObjects() const
{
  // Return vector of all objects
  return objects_;
}

std::vector<std::shared_ptr<GeometricObject>> PlaneImplementation::GetPoints()
    const
{
  // Return only points from vector of all objects_
  auto points = std::vector<std::shared_ptr<GeometricObject>>();
  std::copy_if(objects_.begin(), objects_.end(), std::back_inserter(points),
               [](const std::shared_ptr<GeometricObject>& object)
               { return std::dynamic_pointer_cast<Point>(object); });
  return points;
}

std::vector<std::shared_ptr<GeometricObject>> PlaneImplementation::GetLines()
    const
{
  // Return only lines from vector of all objects_
  auto lines = std::vector<std::shared_ptr<GeometricObject>>();
  std::copy_if(objects_.begin(), objects_.end(), std::back_inserter(lines),
               [](const std::shared_ptr<GeometricObject>& object)
               { return std::dynamic_pointer_cast<Line>(object); });
  return lines;
}

std::vector<std::shared_ptr<GeometricObject>> PlaneImplementation::GetConics()
    const
{
  // Return only conics from vector of all objects_
  auto conics = std::vector<std::shared_ptr<GeometricObject>>();
  std::copy_if(objects_.begin(), objects_.end(), std::back_inserter(conics),
               [](const std::shared_ptr<GeometricObject>& object)
               { return std::dynamic_pointer_cast<Conic>(object); });
  return conics;
}

bool PlaneImplementation::Rename(std::shared_ptr<GeometricObject> object,
                                 const std::string& new_name)
{
  // Check that plane contains object
  if (!IsContained(object.get()))
  {
    assert(false);
    return false;
  }

  const auto old_name = object->GetName();

  object->SetName(new_name);

  return name_generator_.Rename(old_name, new_name);
}

template <class GeometricObjectType>
std::vector<std::shared_ptr<GeometricObject>> PlaneImplementation::GetObjects()
    const
{
  // GeometricObjectType must be base of GeometricObject
  static_assert(std::is_base_of_v<GeometricObject, GeometricObjectType>);

  // Return only GeometricObjectType from vector of all objects_
  auto objects = std::vector<std::shared_ptr<GeometricObject>>();
  std::copy_if(
      objects_.begin(), objects_.end(), std::back_inserter(objects),
      [](const std::shared_ptr<GeometricObject>& object)
      {
        return std::dynamic_pointer_cast<GeometricObjectType, GeometricObject>(
            object);
      });
  return objects;
}

template std::vector<std::shared_ptr<GeometricObject>>
PlaneImplementation::GetObjects<GeometricObject>() const;

template std::vector<std::shared_ptr<GeometricObject>>
PlaneImplementation::GetObjects<Point>() const;

template std::vector<std::shared_ptr<GeometricObject>>
PlaneImplementation::GetObjects<Line>() const;

template std::vector<std::shared_ptr<GeometricObject>>
PlaneImplementation::GetObjects<Conic>() const;