#pragma once
#include "Assert.h"
#include "GeometricObject.h"
#include "Plane.h"

namespace HomoGebra
{
/**
 * \class PointOnPlaneFactory
 * \brief Factory class for constructing points on a plane.
 */
class PointOnPlaneFactory
{
 public:
  /**
   * \brief Constructs a PointOnPlaneFactory object with the given plane.
   *
   * \param plane The plane on which the points will be constructed.
   */
  explicit PointOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a point with the given coordinates.
   *
   * \param equation A place where the point will be constructed.
   *
   * \return Pointer to the constructed point.
   */
  Point* operator()(PointEquation equation) const;

 private:
  Plane* plane_{};
};

/**
 * \struct PointProjectionFactory
 * \brief Factory struct for constructing points projected on a plane.
 */
struct PointProjectionFactory
{
  /**
   * \brief Constructs a PointProjectionFactory object with the given plane.
   *
   * \param plane The plane on which the points will be projected.
   */
  explicit PointProjectionFactory(Plane* plane) : plane_(plane)
  {
    Assert(plane);
  }

  /**
   * \brief Constructs a point on a plane.
   *
   * \param from The point that is projected.
   * \param to The line that is projected on.
   *
   * \return Pointer to the constructed point.
   */
  Point* operator()(Point* from, Line* to) const;

 private:
  Plane* plane_{};
};

/**
 * \struct LineOnPlaneFactory
 * \brief Factory struct for constructing lines on a plane.
 */
struct LineOnPlaneFactory
{
  /**
   * \brief Constructs a LineOnPlaneFactory object with the given plane.
   *
   * \param plane The plane on which the lines will be constructed.
   */
  explicit LineOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a line with the given equation.
   *
   * \param equation The equation of the line.
   *
   * \return Pointer to the constructed line.
   */
  Line* operator()(LineEquation equation) const;

 private:
  Plane* plane_{};
};

/**
 * \struct LineByTwoPointsFactory
 * \brief Factory struct for constructing lines through two points on a plane.
 */
struct LineByTwoPointsFactory
{
  /**
   * \brief Constructs a LineByTwoPointsFactory object with the given plane.
   *
   * \param plane The plane on which the lines will be constructed.
   */
  explicit LineByTwoPointsFactory(Plane* plane) : plane_(plane)
  {
    Assert(plane);
  }

  /**
   * \brief Constructs a line through two given points.
   *
   * \param first The first point to go through.
   * \param second The second point to go through.
   *
   * \return Pointer to the constructed line.
   */
  Line* operator()(Point* first, Point* second) const;

 private:
  Plane* plane_{};
};

/**
 * \struct ConicOnPlaneFactory
 * \brief Factory struct for constructing conics on a plane.
 */
struct ConicOnPlaneFactory
{
  /**
   * \brief Constructs a ConicOnPlaneFactory object with the given plane.
   *
   * \param plane The plane on which the conics will be constructed.
   */
  explicit ConicOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a conic with the given equation.
   *
   * \param equation The equation of the conic.
   *
   * \return Pointer to the constructed conic.
   */
  Conic* operator()(ConicEquation equation) const;

 private:
  Plane* plane_{};
};
}  // namespace HomoGebra