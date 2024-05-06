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

template class ObjectSelector<GeometricObject>;
template class ObjectSelector<Point>;
template class ObjectSelector<Line>;
template class ObjectSelector<Conic>;
}  // namespace HomoGebra