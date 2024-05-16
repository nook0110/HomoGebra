#pragma once
#include "Assert.h"
#include "ButtonElementBody.h"

namespace HomoGebra
{
/**
 * @brief A class that represents an object selector for a specific geometric
 * object type.
 *
 * This class is derived from ObjectSelectorBody and provides functionality to
 * select and update geometric objects of the specified type.
 *
 * @tparam GeometricObjectType The type of geometric object to select.
 */
template <class GeometricObjectType>
class ObjectSelector : public ObjectSelectorBody<GeometricObjectType>
{
 public:
  /**
   * @brief Updates the object selector when an object is removed from the
   * plane.
   *
   * @param object_removed The event data for the object removed event.
   */
  void Update(const PlaneEvent::ObjectRemoved& object_removed) override;

  /**
   * @brief Constructs an ObjectSelector object.
   *
   * @param plane A pointer to the plane on which the object selector operates.
   */
  explicit ObjectSelector(Plane* plane)
      : ObjectSelectorBody<GeometricObjectType>(plane)
  {}

  /**
   * @brief Returns a pointer to the selected geometric object.
   *
   * @return GeometricObjectType* A pointer to the selected geometric object.
   */
  [[nodiscard]] GeometricObjectType* operator()() const;
};

/**
 * @brief A class that wraps a factory for creating objects.
 *
 * This class is derived from Factory and provides additional functionality to
 * draw the factory.
 *
 * @tparam Factory The type of factory to wrap.
 */
template <class Factory>
class FactoryWrapper : public Factory
{
 public:
  /**
   * @brief Constructs a FactoryWrapper object.
   *
   * @param plane A pointer to the plane on which the factory operates.
   */
  explicit FactoryWrapper(Plane* plane) : Factory(plane) {}

  /**
   * @brief Draws the factory.
   */
  void Draw() {}

  /**
   * @brief Calls the wrapped factory with the specified arguments.
   *
   * @tparam Args The types of the arguments.
   * @param arguments The arguments to pass to the factory.
   */
  template <class... Args>
  void operator()(Args&&... arguments) const
  {
    if ((!arguments || ...))
    {
      return;
    }

    Factory::operator()(std::forward<Args>(arguments)...);
  }

  /**
   * @brief Calls the wrapped factory without any arguments.
   */
  void operator()() const { Assert(false); }
};

/**
 * @brief A class that represents a deleter for objects.
 *
 * This class provides functionality to delete objects from the plane.
 */
class Deleter
{
 public:
  /**
   * @brief Constructs a Deleter object.
   *
   * @param plane A pointer to the plane on which the deleter operates.
   */
  explicit Deleter(Plane* plane) : plane_(plane) {}

  /**
   * @brief Draws the deleter.
   */
  void Draw() {}

  /**
   * @brief Calls the deleter with the specified arguments.
   *
   * @tparam Args The types of the arguments.
   * @param arguments The arguments to pass to the deleter.
   */
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
  Plane* plane_{}; /**< A pointer to the plane on which the deleter operates. */
};
}  // namespace HomoGebra
