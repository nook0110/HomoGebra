#pragma once

#include "GeometricObjectImplementation.h"
#include "GeometricObjectBody.h"

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

private:
  /*
  * Member data
  */
  PointBody body_; //!< Body, which you can draw.
  PointImplementation implementation_; //!< Implementation.
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
private:
  /*
  * Member data
  */
  LineBody body_; //!< Body, which you can draw.
  LineImplementation implementation_; //!< Implementation.
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
  ConicBody body_; //!< Body, which you can draw.
  ConicImplementation implementation_; //!< Implementation.
};