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
  * \brief Delete point through implementation
  *
  * \param A reference to an implementation
  */
  void DeletePoint(const PointImplementation& point);

  /**
  * \brief Delete line through implementation
  *
  * \param A reference to an implementation
  */
  void DeleteLine(const LineImplementation& line);

  /**
  * \brief Delete conic through implementation
  *
  * \param A reference to an implementation
  */
  void DeleteConic(const ConicImplementation& conic);
private:
  /**
  * Member data.
  */
  std::vector<Point> points_; //!< All points on the plane.
  std::vector<Line> lines_; //!< All lines on the plane.
  std::vector<Conic> conics_; //!< All conics on the plane.
};
