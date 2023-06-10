#pragma once
#include "GeometricObject.h"
#include "Plane.h"

/**
 * \brief Class that constructs points.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Class constructs points and places them into the plane
 * automatically. It also constructs dependencies between objects. \see
 * Construction
 */
class PointFactory
{
 public:
  /**
   * \brief Construct a factory from the plane.
   *
   * \param plane Instance where to place objects.
   */
  explicit PointFactory(Plane& plane);

  /**
   * \brief Constructs a point with given coordinates.
   *
   * \param equation A place where point will be constructed.
   *
   * \return Pointer to a constructed point.
   */
  Point* OnPlane(PointEquation equation);

  /**
   * \brief Constructs point on a plane.
   *
   * \param from The point that is projected.
   * \param to The line that is projected on.
   *
   * \return Pointer to a constructed point.
   */
  Point* Projection(Point* from, Line* to);

 private:
  /**
   * Member data.
   */
  Plane& plane_;  //!< Plane to add objects.
};

/**
 * \brief Class that constructs lines.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Class constructs lines and places them into the plane automatically.
 * It also constructs dependencies between objects.
 * \see Construction
 */
class LineFactory
{
 public:
  /**
   * \brief Construct a factory from the plane.
   *
   * \param plane Instance where to place objects.
   */
  explicit LineFactory(Plane& plane);

  /**
   * \brief Constructs line through two given points.
   *
   * \param first First point to go through.
   *
   * \param second Second point to go through.
   *
   * \return Pointer to a constructed line.
   */
  Line* ByTwoPoints(Point* first, Point* second);

 private:
  /**
   * Member data.
   */
  Plane& plane_;  //!< Plane to add objects.
};

/**
 * \brief Class that constructs conics.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Class constructs conics and places them into the plane
 * automatically. It also constructs dependencies between objects. \see
 * Construction
 */
class ConicFactory
{
 public:
  /**
   * \brief Construct a factory from the plane.
   *
   * \param plane Instance where to place objects.
   */
  explicit ConicFactory(Plane& plane);

  Conic* OnPlane(ConicEquation equation);

  /**
   * \brief Constructs a conic through five given points.
   *
   * \param first First point to go through.
   * \param second Second point to go through.
   * \param third Third point to go through.
   * \param fourth Fourth point to go through.
   * \param fifth Fifth point to go through.
   * \return Reference to a constructed conic.
   */
  Conic* ByFivePoints(Point* first, Point* second, Point* third, Point* fourth,
                      Point* fifth);

 private:
  /**
   * Member data.
   */
  Plane& plane_;  //!< Plane to add objects.
};
