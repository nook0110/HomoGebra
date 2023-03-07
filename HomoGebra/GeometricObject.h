#pragma once

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"

/**
 * \brief Point on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PointBody
 * \see PointImplementation
 */
class Point 
{
public:
  Point() = delete;

   /**
  * \brief Default destructor.
  *
  */
  ~Point();

  /**
   * \Set new equation of point.
   *
   * \param equation Equation of point
   */
  void SetEquation(const PointEquation& equation);

private:
  /**
  * \brief Construct a point on a plane.
  *
  * \param Reference to a plane where point is constructed.
  */
  explicit Point(Plane& plane);

  /**
  * \brief Notify observers about changes.
  * 
  * \param Event
  */

  /*
   * Member data
   */
  Plane& plane_;                       //!< Plane, where point is constructed.

  PointBody body_;                      //!< Body, which you can draw.
  PointImplementation implementation_;  //!< Implementation.
};

/**
 * \brief Line on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see LineBody
 * \see LineImplementation
 */
class Line 
{
public:
  /**
   * \brief Set new equation of line.
   *
   * \param equation Equation of line
   */
  void SetEquation(const LineEquation& equation);

private:
  /*
   * Member data
   */
  LineBody body_;                      //!< Body, which you can draw.
  LineImplementation implementation_;  //!< Implementation.
};

/**
 * \brief Conic on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see ConicBody
 * \see ConicImplementation
 */
class Conic 
{
private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};