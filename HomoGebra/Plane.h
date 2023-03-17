#pragma once
#include "PlaneBody.h"
#include "PlaneImplementation.h"

/**
 * \brief Container for all objects, which you can draw.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PlaneImplementation
 * \see PlaneBody
 */
class Plane
{
 public:
  /**
   * \brief Add object to plane.
   *
   * \param object Pointer to an object.
   */
  void AddObject(const std::shared_ptr<GeometricObject>& object);

  /**
   * \brief Get all objects.
   *
   * \return All objects.
   */
  [[nodiscard]] const std::vector<std::shared_ptr<GeometricObject>>&
  GetObjects() const;

  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetPoints() const;

  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetLines() const;

  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetConics() const;

 private:
  PlaneImplementation implementation_;
  PlaneBody body_;
};
