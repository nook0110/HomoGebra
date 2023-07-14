#pragma once

#include <functional>

#include "GeometricObjectFactory.h"
#include "Widget.h"

/**
 * \brief Wrapper of Factory function into a callable object.
 *
 * \details sth like std::bind
 *
 * \tparam Factory Type of factory.
 * \tparam ConstructorFunction Callable member function.
 *
 * \see PointFactory
 * \see LineFactory
 * \see ConicFactory
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
template <class Factory, class ConstructorFunction>
class FactoryWrapper
{
 public:
  /**
   * \brief Constructor by factory and callable member-func.
   *
   * \param factory Factory.
   * \param constructor_function Callable member function.
   */
  FactoryWrapper(Factory factory, ConstructorFunction constructor_function)
      : factory_(std::move(factory)),
        constructor_function_(std::move(constructor_function))
  {}

  /**
   * \brief Call member function with args.
   *
   * \tparam Args Types of args.
   *
   * \param args Args.
   *
   * \return Object created by factory.
   */
  template <class... Args>
  auto operator()(Args&&... args)
  {
    return constructor_function_(&factory_, std::forward<Args>(args)...);
  }

 private:
  Factory factory_;                           //!< Factory.
  ConstructorFunction constructor_function_;  //!< Callable member function.
};

/**
 * \brief Wrapper of ObjectSelector to rename some functions.
 *
 * \tparam ObjectType Type of object.
 *
 * \see Gui::Constructor::ObjectSelector
 */
template <class ObjectType>
class ObjectSelectorWrapper
    : public Gui::Constructor::ObjectSelector<ObjectType>
{
 public:
  /**
   * \brief Constructor by plane.
   *
   * \param plane Plane.
   */
  explicit ObjectSelectorWrapper(Plane& plane)
      : Gui::Constructor::ObjectSelector(plane)
  {}

  /**
   * \brief Wrap of GetObject();
   *
   * \return Object that was selected.
   */
  auto operator()()
  {
    return Gui::Constructor::ObjectSelector<ObjectType>::GetObject();
  }

  /**
   * \brief Wrap of SetObject
   *
   * \param object Object to select.
   */
  void SetArgument(ObjectType* object)
  {
    Gui::Constructor::ObjectSelector<ObjectType>::SetObject(object);
  }

  /**
   * \brief Is object selected?
   *
   * \return True if object is selected, false otherwise.
   */
  bool IsSet() { return operator()(); }
};

using PointSelectorWrapper = ObjectSelectorWrapper<Point>;
using LineSelectorWrapper = ObjectSelectorWrapper<Line>;
using ConicSelectorWrapper = ObjectSelectorWrapper<Conic>;

/**
 * \brief Wrapper of LineFactory::ByTwoPoints
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class LineByTwoPointsWrapper
    : public FactoryWrapper<LineFactory,
                            std::function<Line*(LineFactory*, Point*, Point*)>>
{
 public:
  /**
   * \brief Constructor by plane.
   *
   * \param plane Plane.
   */
  explicit LineByTwoPointsWrapper(Plane& plane)
      : FactoryWrapper(LineFactory(plane),
                       [](LineFactory* factory, Point* first, Point* second)
                       { return factory->ByTwoPoints(first, second); })
  {}
};
