#include "ButtonElement.h"

template <class GeometricObjectType>
GeometricObjectType* ObjectSelector<GeometricObjectType>::operator()() const
{
  return ObjectSelectorBody<GeometricObjectType>::GetObject();
}