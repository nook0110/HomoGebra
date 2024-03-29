﻿#include "PlaneImplementation.h"

#include <functional>

#include "Assert.h"
#include "Construction.h"
#include "GeometricObject.h"

namespace HomoGebra
{
void PlaneImplementation::AddConstruction(
    std::unique_ptr<Construction> construction)
{
  // Attach plane as an observer to object
  construction->GetObject()->Attach(this);

  // Add object to vector of all objects
  construction_.push_back(std::move(construction));
}

void PlaneImplementation::DestroyObject(const GeometricObject* object)
{
  object->AlertDestruction();

  // Delete object from vector of all objects
  while (!going_to_be_destroyed_.Empty())
  {
    const auto destroying_object = going_to_be_destroyed_.Pop();

    RemoveObject(destroying_object);
  }
}

bool PlaneImplementation::IsContained(const GeometricObject* object) const
{
  // Check if object is in vector of all objects
  return std::ranges::find_if(
             construction_,
             [object](const std::unique_ptr<Construction>& construction) {
               return construction->GetObject() == object;
             }) != construction_.end();
}

const NameGenerator& PlaneImplementation::GetNameGenerator() const
{
  return name_generator_;
}

void PlaneImplementation::Update(const ObjectEvent::Moved& moved_event)
{
  /*
   * Nothing to do here
   */
}

void PlaneImplementation::Update(
    const ObjectEvent::GoingToBeDestroyed& destroyed_event)
{
  // Remove object from vector of all objects
  going_to_be_destroyed_.Append(destroyed_event.object);
}

void PlaneImplementation::Update(const ObjectEvent::Renamed& renamed_event)
{
  Expect(renamed_event.object->GetName() == renamed_event.new_name,
         "Object name isn't correct!");

  name_generator_.DeleteName(renamed_event.old_name);

  auto adjust_name = [this, renamed_event]
  {
    const auto new_name = name_generator_.GenerateName(renamed_event.new_name);

    name_generator_.AddName(new_name);

    renamed_event.object->SetName(static_cast<std::string>(new_name));
  };

  if (!name_generator_.AddName(renamed_event.new_name))
  {
    adjust_name();
  }
}

void PlaneImplementation::RemoveObject(const GeometricObject* object)
{
  Notify(PlaneEvent::ObjectRemoved{object});

  name_generator_.DeleteName(object->GetName());

  std::erase_if(construction_,
                [object](const std::unique_ptr<Construction>& construction)
                { return construction->GetObject() == object; });
}

template <class GeometricObjectType>
std::vector<GeometricObject*> PlaneImplementation::GetObjects() const
{
  // GeometricObjectType must be base of GeometricObject
  static_assert(std::is_base_of_v<GeometricObject, GeometricObjectType>);

  // Return only GeometricObjectType from vector of all objects_
  auto objects = std::vector<GeometricObject*>();

  // Transform vector of unique ptr-s to raw ptr-s
  std::transform(construction_.begin(), construction_.end(),
                 std::back_inserter(objects),
                 [](const std::unique_ptr<Construction>& construction)
                 { return construction->GetObject(); });

  // Remove objects that are not of type GeometricObjectType
  objects.erase(
      std::remove_if(objects.begin(), objects.end(),
                     [](const GeometricObject* object) {
                       return !dynamic_cast<const GeometricObjectType*>(object);
                     }),
      objects.end());

  return objects;
}

template std::vector<GeometricObject*>
PlaneImplementation::GetObjects<GeometricObject>() const;

template std::vector<GeometricObject*> PlaneImplementation::GetObjects<Point>()
    const;

template std::vector<GeometricObject*> PlaneImplementation::GetObjects<Line>()
    const;

template std::vector<GeometricObject*> PlaneImplementation::GetObjects<Conic>()
    const;
}  // namespace HomoGebra