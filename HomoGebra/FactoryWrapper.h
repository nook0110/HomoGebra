#pragma once

#include <functional>

#include "GeometricObjectFactory.h"
#include "Widget.h"

template <class Factory, class ConstructorFunction>
class FactoryWrapper
{
 public:
  FactoryWrapper(Factory factory, ConstructorFunction constructor_function)
      : factory_(std::move(factory)),
        constructor_function_(std::move(constructor_function))
  {}

  template <class... Args>
  auto operator()(Args&&... args)
  {
    return constructor_function_(&factory_, std::forward<Args>(args)...);
  }

 private:
  Factory factory_;
  ConstructorFunction constructor_function_;
};

template <class ObjectSelector>
class ObjectSelectorWrapper : public ObjectSelector
{
 public:
  using ObjectType = typename ObjectSelector::value_type;
  ObjectSelectorWrapper(Plane& plane) : ObjectSelector(plane) {}

  auto operator()() { return ObjectSelector::GetObject(); }

  void SetArgument(ObjectType* object) { ObjectSelector::SetObject(object); }

  bool IsSet() { return operator()(); }
};

using PointSelectorWrapper =
    ObjectSelectorWrapper<Gui::Constructor::ObjectSelector<Point>>;
using LineSelectorWrapper =
    ObjectSelectorWrapper<Gui::Constructor::ObjectSelector<Line>>;
using ConicSelectorWrapper =
    ObjectSelectorWrapper<Gui::Constructor::ObjectSelector<Conic>>;

class LineByTwoPointsWrapper
    : public FactoryWrapper<LineFactory,
                            std::function<Line*(LineFactory*, Point*, Point*)>>
{
 public:
  explicit LineByTwoPointsWrapper(Plane& plane)
      : FactoryWrapper(LineFactory(plane),
                       [](LineFactory* factory, Point* first, Point* second)
                       { return factory->ByTwoPoints(first, second); })
  {}
};
