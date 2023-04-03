#pragma once
#include "GeometricObject.h"

/**
 * \brief Construction that loses its properties after projective
 * transformation.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 *
 * \see StrongTransformation
 */
class WeekConstruction
{
 public:
  /**
   * \brief Gets transformation which was applied on the object.
   *
   * \return Transformation which was applied on the object.
   */
  [[nodiscard]] const Transformation& GetTransformation() const;

 private:
  Transformation
      transformation_;  //!< Transformation which was applied on the object.
};

/**
 * \brief Construction that does not lose its properties after projective
 * transformation.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 *
 * \see WeekTransformation
 */
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
   * \brief Default destructor.
   *
   */
  ~Construction() override = default;

 protected:
  /**
   * \brief Constructor deleted.
   *
   */
  Construction() = default;
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
   * \brief Default destructor.
   *
   */
  ~ConstructionPoint() override = default;

  /**
   * \brief Recalculate equation of point.
   *
   * \return New equation of point.
   */
  [[nodiscard]] virtual PointEquation RecalculateEquation() const = 0;

  /**
   * \brief Update the object because sth was moved.
   *
   * \param event Tag [Event::Moved] for tag dispatch
   */
  void Update(const Event::Moved& event) override;

  /**
   * \brief Update the object because sth was destroyed.
   *
   * \param event Tag [Event::Destroyed] for tag dispatch.
   */
  void Update(const Event::Destroyed& event) override;

 protected:
  /**
   * \brief Constructor deleted.
   *
   */
  ConstructionPoint() = default;

  /**
   * \brief Get equation of point.
   *
   * \return Equation of point.
   */
  [[nodiscard]] const PointEquation& GetEquation() const;

  /**
   * \brief Set equation of point.
   *
   * \param equation Equation of point.
   */
  void SetEquation(const PointEquation& equation);

 private:
  std::shared_ptr<Point> point_;  //!< Point, which is created.
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
  [[nodiscard]] PointEquation RecalculateEquation() const override;
};

/**
 * \brief Construction of a point by intersection of two lines.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class ConstructionFromTwoLines : public ConstructionPoint
{};

/**
 * \brief Defines how line is created.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 *
 * \details Updates position of line
 */
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
  [[nodiscard]] virtual LineEquation RecalculateEquation() const = 0;

  /**
   * \brief Update object because sth moved.
   *
   * \param event Tag for tag dispatch
   */
  void Update(const Event::Moved& event) override;

  /**
   * \brief Update object because sth destroyed.
   *
   * \param event Tag for tag dispatch
   */
  void Update(const Event::Destroyed& event) override;

 protected:
  /**
   * \brief Get equation of line.
   *
   * \return Equation of line.
   */
  [[nodiscard]] const LineEquation& GetEquation() const;

  /**
   * \brief Set equation of line.
   *
   * \param equation Equation of line.
   */
  void SetEquation(const LineEquation& equation);

 private:
  std::shared_ptr<Line> line_;  //!< Line, which is created.
};
