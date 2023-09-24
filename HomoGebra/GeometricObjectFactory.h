#pragma once
#include "Assert.h"
#include "GeometricObject.h"
#include "Plane.h"

class PointOnPlaneFactory
{
 public:
  explicit PointOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a point with given coordinates.
   *
   * \param equation A place where point will be constructed.
   *
   * \return Pointer to a constructed point.
   */
  Point* operator()(PointEquation equation) const;

 private:
  Plane* plane_{};
};

struct PointProjectionFactory
{
  explicit PointProjectionFactory(Plane* plane) : plane_(plane)
  {
    Assert(plane);
  }

  /**
   * \brief Constructs point on a plane.
   *
   * \param from The point that is projected.
   * \param to The line that is projected on.
   *
   * \return Pointer to a constructed point.
   */
  Point* operator()(Point* from, Line* to) const;

 private:
  Plane* plane_{};
};

struct LineOnPlaneFactory
{
  explicit LineOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a line with given equation.
   *
   * \param equation Equation of a line.
   *
   * \return Pointer to a constructed line.
   */
  Line* operator()(LineEquation equation) const;

 private:
  Plane* plane_{};
};

struct LineByTwoPointsFactory
{
  explicit LineByTwoPointsFactory(Plane* plane) : plane_(plane)
  {
    Assert(plane);
  }

  /**
   * \brief Constructs line through two given points.
   *
   * \param first First point to go through.
   * \param second Second point to go through.
   *
   * \return Pointer to a constructed line.
   */
  Line* operator()(Point* first, Point* second) const;

 private:
  Plane* plane_{};
};

struct ConicOnPlaneFactory
{
  explicit ConicOnPlaneFactory(Plane* plane) : plane_(plane) { Assert(plane); }

  /**
   * \brief Constructs a conic with given equation.
   *
   * \param equation Equation of a conic.
   *
   * \return Pointer to a constructed conic.
   */
  Conic* operator()(ConicEquation equation) const;

 private:
  Plane* plane_{};
};