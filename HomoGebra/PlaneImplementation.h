#pragma once
#include <vector>

#include "GeometricObject.h"

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
   * \breif Get all conics.
   *
   * \return Conics on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetConics() const;

 private:
  /**
   * Member data.
   */

  std::vector<std::shared_ptr<GeometricObject>>
      objects_;  //!< All objects on the plane.
};
