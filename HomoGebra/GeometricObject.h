#pragma once

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"

class GeometricObject
{
public:
  /**
  * \brief Default destructor.
  */
  virtual ~GeometricObject() = default;

  /**
  * \brief Destroy this object.
  *
  * \param plane Plane, where this object is located.
  */
  virtual void Destroy(Plane& plane) = 0;

protected:
  GeometricObject() = default;
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
  ~Point() final = default;

  /**
  * \brief Destroy this object.
  *
  * \param plane Plane, where this object is located.
  */
  void Destroy(Plane& plane) final;

  /**
  * \brief Notify observers that this objected is destroyed
  *
  * \param event Event
  */
  void Notify(const Event::Destroyed& event) const;

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
  * \brief Default destructor.
  *
  */
  ~Line() final = default;

  /**
  * \brief Destroy this object.
  *
  * \param plane Plane, where this object is located.
  */
  void Destroy(Plane& plane) final;

  /**
  * \brief Notify observers that this objected is destroyed
  *
  * \param event Event
  */
  void Notify(const Event::Destroyed& event) const;

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
public:
  /**
  * \brief Destroy this object.
  *
  * \param plane Plane, where this object is located.
  */
  void Destroy(Plane& plane) final;

  /**
  * \brief Notify observers that this objected is destroyed
  *
  * \param event Event
  */
  void Notify(const Event::Destroyed& event) const;

private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};