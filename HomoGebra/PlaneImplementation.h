#pragma once
#include <memory>
#include <vector>

#include "NameGenerator.h"
#include "Observer.h"

class GeometricObject;
class Construction;

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
class PlaneImplementation : public GeometricObjectObserver
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
  void RemoveObject(const GeometricObject* object);

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
  void Update(const ObjectEvent::Destroyed& destroyed_event) override;
  void Update(const ObjectEvent::Renamed& renamed_event) override;

 private:
  /**
   * Member data.
   */

  std::vector<std::unique_ptr<Construction>>
      construction_;  //!< All constructions on the plane.

  NameGenerator name_generator_;  //!< Name generator.
};
