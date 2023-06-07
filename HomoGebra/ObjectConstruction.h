#pragma once

#include "Construction.h"
#include "GeometricObject.h"

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

  [[nodiscard]] GeometricObject* GetObject() override;

  [[nodiscard]] Point* GetPoint();

  /**
   * \brief Recalculate equation of point.
   *
   * \return New equation of point.
   */
  [[nodiscard]] virtual PointEquation RecalculateEquation() const = 0;

  void Update(const Event::Moved& event) override;

  void Update(const Event::Destroyed& event) override;

  void Update(const Event::Renamed& event) override;

 protected:
  /**
   * \brief Default constructor.
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
  void SetEquation(PointEquation equation);

 private:
  Point point_;  //!< Point, which is created.
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
class PointOnPlane : public ConstructionPoint, public StrongConstruction
{
 public:
  explicit PointOnPlane(PointEquation equation);

  ~PointOnPlane() override = default;

  /**
   * \brief Recalculate equation of point.
   *
   * \return New equation of point.
   */
  [[nodiscard]] PointEquation RecalculateEquation() const override;

 private:
  PointEquation equation_;  //!< Equation of point.
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
   * \brief Default destructor.
   */
  ~ConstructionLine() override = default;

  GeometricObject* GetObject() override;

  Line* GetLine();

  /**
   * Recalculate equation of line.
   */
  virtual void RecalculateEquation() = 0;

  void Update(const Event::Moved& event) override;

  void Update(const Event::Destroyed& event) override;

  void Update(const Event::Renamed& event) override;

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
  Line line_;  //!< Line, which is created.
};

class ByTwoPoints final : public ConstructionLine, public StrongConstruction
{
 public:
  ByTwoPoints(Point* first_point, Point* second_point);

  void RecalculateEquation() override;

 private:
  Point* first_point_;
  Point* second_point_;
};

class ConstructionConic : public Construction
{
 public:
 private:
  Conic conic_;
};

class ConicOnPlane final : public ConstructionConic, public StrongConstruction
{
 public:
  explicit ConicOnPlane(ConicEquation equation);

  void Update(const Event::Moved& event) override;

  void Update(const Event::Destroyed& event) override;

  void Update(const Event::Renamed& event) override;

 private:
  ConicEquation equation_;
};
