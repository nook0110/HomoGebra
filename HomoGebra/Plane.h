#pragma once
#include "PlaneImplementation.h"
#include "PlaneBody.h"

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

private:
  PlaneImplementation implementation_;
  PlaneBody body_;
};
