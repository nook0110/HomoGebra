﻿#include "PlaneImplementation.h"

#include <functional>

#include "GeometricObject.h"

void PlaneImplementation::AddObject(std::shared_ptr<GeometricObject> object)
{
  // Attach plane as an observer to object
  object->Attach(std::shared_ptr<GeometricObjectObserver>(this));

  // Add object to vector of all objects
  objects_.push_back(std::move(object));
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

const NameGenerator& PlaneImplementation::GetNameGenerator() const
{
  return name_generator_;
}

void PlaneImplementation::Update(const Event::Moved& moved_event)
{
  /*
   * Nothing to do here
   */
}

void PlaneImplementation::Update(const Event::Destroyed& destroyed_event)
{
  // Remove object from vector of all objects
  RemoveObject(destroyed_event.object);
}

void PlaneImplementation::Update(const Event::Renamed& renamed_event)
{
  // Check if object has no name
  if (renamed_event.object->GetName().empty())
  {
    if (!name_generator_.AddName(renamed_event.new_name))
    {
      renamed_event.object->SetName(static_cast<std::string>(
          name_generator_.GenerateName(renamed_event.new_name)));
    }
    return;
  }

  if (!name_generator_.Rename(renamed_event.object->GetName(),
                              renamed_event.new_name))
  {
    renamed_event.object->SetName(static_cast<std::string>(
        name_generator_.GenerateName(renamed_event.new_name)));
  }
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