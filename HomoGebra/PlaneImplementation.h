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
 * \brief Construct point
 *
 * \param A coordinate where to construct
 *
 * \return A reference to a constructed point
 */
  Point& EmplacePoint(const PointEquation& equation);

  /**
  * \brief Construct line
  *
  * \param A coordinate where to construct
  *
  * \return A reference to a constructed line
  */
  Line& EmplaceLine(const LineEquation& equation);

  /**
  * \brief Construct conic
  *
  * \param A coordinate where to construct
  *
  * \return A reference to a constructed conic
  */
  Conic& EmplaceConic(const ConicEquation& equation);

  /**
  * \brief Delete point
  *
  * \param A reference to a point
  */
  void DeletePoint(const Point& point);

  /**
  * \brief Delete line
  *
  * \param A reference to a line
  */
  void DeleteLine(const Line& line);

  /**
  * \brief Delete conic
  *
  * \param A reference to a conic
  */
  void DeleteConic(const Conic& conic);
private:

  /**
  * Member data.
  */
  std::vector<Point> points_; //!< All points on the plane.
  std::vector<Line> lines_; //!< All lines on the plane.
  std::vector<Conic> conics_; //!< All conics on the plane.
};
