#pragma once
#include "GeometricObject.h"

/**
 * \brief Class that constructs geometric objects
 * \author nook0110
 * \version 0.1
 * \date Februrary 2023
 * This class incapsulates 
*/
class PointFactory
{
public:

  /// Point:

  /**
   * \brief Constructs point on a plane with given coordinates
   * \param coordinate   Place where point will be constructed
   * \return Point&
   */
  Point& OnPlane(const PointCoordinate& coordinate);
  Point& Projection();

  /// Line:

  Line& ByTwoPoints();

  /// Conic:

  Conic& ByFivePoints();

private:

};
