#pragma once
#include "Assert.h"
#include "ButtonElementBody.h"

template <class GeometricObjectType>
class ObjectSelector : public ObjectSelectorBody<GeometricObjectType>
{
 public:
  explicit ObjectSelector(Plane* plane)
      : ObjectSelectorBody<GeometricObjectType>(plane)
  {}

  [[nodiscard]] GeometricObjectType* operator()() const;
};

template <class Factory>
class FactoryWrapper : public Factory
{
 public:
  explicit FactoryWrapper(Plane* plane) : Factory(plane) {}

  void Draw() {}

  template <class... Args>
  void operator()(Args&&... arguments) const
  {
    if ((!arguments || ...))
    {
      return;
    }

    Factory::operator()(std::forward<Args>(arguments)...);
  }

  void operator()() const { Assert(false); }
};

template ObjectSelector<GeometricObject>;
template ObjectSelector<Point>;
template ObjectSelector<Line>;
template ObjectSelector<Conic>;
