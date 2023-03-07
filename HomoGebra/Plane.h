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
  * \brief Destroy point
  * 
  * \param Point to destroy
  */
  void DeletePoint(const Point& point);

  /**
  * \brief Destroy line
  * 
  * \param Line to destroy
  */
  void DeleteLine(const Line& line);

  /**
  * \brief Destroy conic
  * 
  * \param Conic to destroy
  */
  void DeleteConic(const Conic& conic);
private:
  PlaneImplementation implementation_;
  PlaneBody body_;
};
