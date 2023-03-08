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
  * \param Object to add
  */
  void AddObject(const std::shared_ptr<GeometricObject>& object);

  /**
  * \brief Remove object
  *
  * \param Object to destroy
  */
  void RemoveObject(GeometricObject* object);

private:

  /**
  * Member data.
  */

  std::vector<std::shared_ptr<GeometricObject>> objects_; //!< All objects on the plane.
};
