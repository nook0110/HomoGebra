#pragma once

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"

class GeometricObject
{
};

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
class Point : public GeometricObject
{
public:

  /**
  * \brief Construct point on a plane with equation.
  *
  * \param equation Equation of point.
  */
  explicit Point(const PointEquation& equation = PointEquation{});

  /**
 * \brief Default destructor.
 *
 */
  ~Point();

  /**
   * \brief Set new equation of point.
   *
   * \param equation Equation of point
   */
  void SetEquation(const PointEquation& equation);

  /**
  * \brief Return current equation of point.
  * 
  * \return Equation of point
  */
  const PointEquation& GetEquation() const;

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
class Line : public GeometricObject
{
public:

  /**
  * \brief Construct line on a plane with equation.
  *
  * \param equation Equation of line
  */
  explicit Line(const LineEquation& equation = LineEquation{});

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
class Conic : public GeometricObject
{
private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};