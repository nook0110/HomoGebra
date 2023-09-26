#pragma once
#include <memory>
#include <vector>

#include "NameGenerator.h"
#include "Observer.h"

namespace HomoGebra
{
class GeometricObject;
class Construction;

class GarbageObjectCollector
{
 public:
  [[nodiscard]] bool Empty() const { return objects_.empty(); }

  void Append(const GeometricObject* object) { objects_.emplace_back(object); }

  const GeometricObject* Pop()
  {
    const auto last = objects_.back();
    objects_.pop_back();
    return last;
  }

  void Clear() { objects_.clear(); }

 private:
  std::vector<const GeometricObject*> objects_;
};

/**
 * \brief Implementation of Plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Class that manages all objects.
 *
 * \see Plane
 */
class PlaneImplementation : public GeometricObjectObserver,
                            public ObservablePlane
{
 public:
  /**
   * \brief Adds object
   *
   * \param construction Object to add
   */
  void AddConstruction(std::unique_ptr<Construction> construction);

  /**
   * \brief Remove object.
   *
   * \param object Object to destroy.
   */
  void DestroyObject(const GeometricObject* object);

  /**
   * \brief Check if object is contained.
   *
   * \param object Object to check.
   *
   * \return True if object is contained, false otherwise.
   */
  [[nodiscard]] bool IsContained(const GeometricObject* object) const;

  /**
   * \brief Get all objects of GeometricObjectType.
   *
   * \tparam GeometricObjectType Type of geometric object to get.
   *
   * \return Objects of GeometricObjectType.
   */
  template <class GeometricObjectType>
  [[nodiscard]] std::vector<GeometricObject*> GetObjects() const;

  /**
   * \brief Get name generator.
   *
   * \return Name generator.
   */
  [[nodiscard]] const NameGenerator& GetNameGenerator() const;

  void Update(const ObjectEvent::Moved& moved_event) override;
  void Update(const ObjectEvent::GoingToBeDestroyed& destroyed_event) override;
  void Update(const ObjectEvent::Renamed& renamed_event) override;

 private:
  void RemoveObject(const GeometricObject* object);

  /**
   * Member data.
   */

  std::vector<std::unique_ptr<Construction>>
      construction_;  //!< All constructions on the plane.

  NameGenerator name_generator_;  //!< Name generator.

  GarbageObjectCollector going_to_be_destroyed_;
};
}  // namespace HomoGebra