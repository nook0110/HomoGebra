#pragma once
#include <memory>
#include <vector>

#include "NameGenerator.h"

class GeometricObject;

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
class PlaneImplementation
{
 public:
  /**
   * \brief Adds object
   *
   * \param object Object to add
   */
  void AddObject(const std::shared_ptr<GeometricObject>& object);

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
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetObjects()
      const;

  /**
   * \brief Get all objects.
   *
   * \return All objects on plane.
   */
  [[nodiscard]] const std::vector<std::shared_ptr<GeometricObject>>&
  GetObjects() const;

  /**
   * \brief Get all points.
   *
   * \return Points on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetPoints() const;

  /**
   * \brief Get all lines.
   *
   * \return Lines on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetLines() const;

  /**
   * \brief Get all conics.
   *
   * \return Conics on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetConics() const;

  /**
   * \brief Renames object.
   *
   * \param object Object to rename.
   * \param new_name New name.
   *
   * \return True if object was renamed, false otherwise.
   */
  bool Rename(const std::shared_ptr<GeometricObject>& object,
              const std::string& new_name);

  /**
   * \brief Get name generator.
   *
   * \return Name generator.
   */
  [[nodiscard]] const NameGenerator& GetNameGenerator() const;

 private:
  /**
   * Member data.
   */

  std::vector<std::shared_ptr<GeometricObject>>
      objects_;  //!< All objects on the plane.

  NameGenerator name_generator_;  //!< Name generator.
};
