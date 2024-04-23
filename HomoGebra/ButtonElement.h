#pragma once
#include "Assert.h"
#include "ButtonElementBody.h"

namespace HomoGebra
{
template <class GeometricObjectType>
class ObjectSelector : public ObjectSelectorBody<GeometricObjectType>
{
 public:
  void Update(const PlaneEvent::ObjectRemoved& object_removed) override;

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

class Deleter
{
 public:
  explicit Deleter(Plane* plane) : plane_(plane) {}

  void Draw() {}

  void operator()() const { Assert(false); }

  template <class... Args>
  void operator()(Args&&... arguments) const
  {
    if ((!arguments || ...))
    {
      return;
    }

    (plane_->DeleteObject(arguments), ...);
  }

 private:
  Plane* plane_{};
};
}  // namespace HomoGebra
