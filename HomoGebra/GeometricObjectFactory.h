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
 * \details Class constructs points and places them into the plane automatically.
 * It also constructs dependencies between objects.
 * \see Construction
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
   * \param coordinate A place where point will be constructed.
   *
   * \return Point& Reference to a constructed point.
   */
  Point& OnPlane(const PointEquation& coordinate);

  /**
   * \brief Constructs point on a plane.
   *
   * \param from The point that is projected.
   *
   * \return Reference to a constructed point.
   */
  Point& Projection(const Point& from, const Line& to);

private:
  /**
   * Member data.
   */
  Plane& plane_; //!< Plane to add objects.
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
   * \return Reference to a constructed line.
   */
  Line& ByTwoPoints(const Point& first, const Point& second);

private:
  /**
   * Member data.
   */
  Plane& plane_; //!< Plane to add objects.
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
 * \details Class constructs conics and places them into the plane automatically.
 * It also constructs dependencies between objects.
 * \see Construction
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
  Conic& ByFivePoints(const Point& first, const Point& second,
                      const Point& third, const Point& fourth,
                      const Point& fifth);

private:
  /**
   * Member data.
   */
  Plane& plane_; //!< Plane to add objects.
};
