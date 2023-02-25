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
class Point {
 public:
  /**
   * \Set new equation of point.
   *
   * \param equation Equation of point
   */
  void SetEquation(const PointEquation& equation);

 /**
  * \brief 
 */

 private:
  /*
   * Member data
   */
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
class Line {
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
class Conic {
 private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};