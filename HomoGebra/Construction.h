#pragma once
#include "GeometricObject.h"

class WeekConstruction
{
public:

  const Transformation& GetTransformation() const;

private:
  Transformation tranformation_;
};

class StrongConstruction
{};

/**
 * \brief Defines how object is created.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Updates positions of objects
 * \see GeometricObjectImplementation
*/
class Construction : public ConstructionObserver
{
public:
  /**
   * \brief Constructor deleted.
   *
   */
  Construction() = delete;

  /**
   * \brief Default destructor.
   *
   */
  ~Construction() override = default;
};

/**
 * \brief Defines how point is created.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Updates position of point
*/
class ConstructionPoint : public Construction
{
public:
  /**
   * \brief Constructor deleted.
   *
   */
  ConstructionPoint() = delete;

  /**
  * \brief Default destructor.
  *
  */
  ~ConstructionPoint() override = default;

  /**
   * \brief Recalculate equation of point.
   *
   * \return New equation of point.
   */
  virtual PointEquation RecalculateEquation() const = 0;

  /**
   * \brief Update the object because sth was moved.
   *
   * \param Tag [Event::Moved] for tag dispatch
   */
  void Update(const Event::Moved&) override;

  /**
  * \brief Update the object because sth was destroyed.
  *
  * \param Tag [Event::Destroyed] for tag dispatch.
  */
  void Update(const Event::Destroyed&) override;
protected:

  /**
  * \brief Get equation of point.
  *
  * \return Equation of point.
  */
  const PointEquation& GetEquation() const;

  /**
  * \brief Set equation of point.
  *
  * \param equation Equation of point.
  */
  void SetEquation(const PointEquation& equation);

private:
  std::shared_ptr<Point> point_; //!< Point, which is created.
};

/**
 * \brief Construction of a casual point on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Have no dependence on other objects
*/
class ConstructionOnPlane : public ConstructionPoint, public StrongConstruction
{
public:
  ~ConstructionOnPlane() override = default;

  /**
  * \brief Recalculate equation of point.
  *
  * \return New equation of point.
  */
  PointEquation RecalculateEquation() const override;
};

class ConstructionFromTwoLines : public ConstructionPoint
{};

class ConstructionLine : public Construction
{
public:
  /**
   * \brief Constructor deleted.
   */
  ConstructionLine() = delete;

  /**
   * \brief Default destructor.
   */
  ~ConstructionLine() override = default;

  /**
   * Recalculate equation of point.
   *
   * \return New equation of point.
   */
  virtual LineEquation RecalculateEquation() const = 0;

  /**
   * \brief Update object because sth moved.
   *
   * \param Tag for tag dispatch
   */
  void Update(const Event::Moved&) override;

  /**
  * \brief Update object because sth destroyed.
  *
  * \param Tag for tag dispatch
  */
  void Update(const Event::Destroyed&) override;
protected:
  /**
  * \brief Get equation of line.
  *
  * \return Equation of line.
  */
  const LineEquation& GetEquation() const;

  /**
  * \brief Set equation of line.
  *
  * \param equation Equation of line.
  */
  void SetEquation(const LineEquation& equation);

private:
  std::shared_ptr<Line> line_; //!< Line, which is created.
};

class ConstructionConic : public Construction
{};