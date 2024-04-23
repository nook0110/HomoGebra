#include "ButtonElement.h"

namespace HomoGebra
{
template <class GeometricObjectType>
void ObjectSelector<GeometricObjectType>::Update(
    const PlaneEvent::ObjectRemoved& object_removed)
{
  if (ObjectSelectorBody<GeometricObjectType>::GetObject() ==
      object_removed.removed_object)
    ObjectSelectorBody<GeometricObjectType>::SetObject(nullptr);
}

template <class GeometricObjectType>
GeometricObjectType* ObjectSelector<GeometricObjectType>::operator()() const
{
  return ObjectSelectorBody<GeometricObjectType>::GetObject();
}

template ObjectSelector<GeometricObject>;
template ObjectSelector<Point>;
template ObjectSelector<Line>;
template ObjectSelector<Conic>;
}  // namespace HomoGebra