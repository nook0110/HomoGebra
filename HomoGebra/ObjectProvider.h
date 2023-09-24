#pragma once
#include "Plane.h"

/**
 * \brief Class that finds objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class ObjectProvider
{
 public:
  /**
   * \brief Constructs an object provider from the plane.
   *
   * \param plane Instance where to place objects.
   */
  explicit ObjectProvider(Plane* plane);

  /**
   * \brief Gets a nearest object.
   *
   * \tparam GeometricObjectType Type of object to get.
   *
   * \param position Position to find object.
   * \param max_distance Maximum distance to find object.
   *
   * \return Nearest object.
   */
  template <class GeometricObjectType>
  GeometricObjectType* GetNearestObject(
      const sf::Vector2f& position,
      float max_distance = std::numeric_limits<float>::max());

 private:
  /**
   * Member data.
   */
  Plane* plane_;  //!< Plane to add objects.
};
