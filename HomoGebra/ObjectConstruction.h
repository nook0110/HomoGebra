#pragma once

#include "Construction.h"
#include "Equation.h"

namespace HomoGebra
{
class GeometricObject;
class Point;
class Conic;
class Line;

/**
 * \brief Base class for all point constructions.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 *
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
   * \brief Gets object that is constructed.
   *
   * \return Object that is constructed.
   */
  [[nodiscard]] GeometricObject* GetObject() const override;

  /**
   * \brief Gets point that is constructed.
   *
   * \return Point that is constructed.
   */
  [[nodiscard]] Point* GetPoint() const;

  /**
   * \brief Recalculate equation of point.
   */
  void RecalculateEquation() override = 0;

  /**
   * \brief Update point when something is destroyed.
   *
   * \param event Event of destruction.
   */
  void Update(const ObjectEvent::GoingToBeDestroyed& event) override;

  /**
   * \brief Update point when something is renamed
   *
   * \param renamed_event Event of renaming.
   */
  void Update(const ObjectEvent::Renamed& renamed_event) override;

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
  void SetEquation(PointEquation equation) const;

 private:
  std::unique_ptr<Point> point_ =
      std::make_unique<Point>();  //!< Point, which is created.
};

/**
 * \brief Construction of a casual point on a plane.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 *
 * \details Have no dependence on other objects
 */
class PointOnPlane : public ConstructionPoint, public StrongConstruction
{
 public:
  /**
   * \brief Constructs point by equation
   *
   * \param equation Equation of point.
   */
  explicit PointOnPlane(PointEquation equation);

  /**
   * \brief Default destructor.
   *
   */
  ~PointOnPlane() override = default;

  /**
   * \brief Recalculate equation of point.
   *
   */
  void RecalculateEquation() override;

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
 * \brief Base class for all line constructions.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
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

  /**
   * \brief Gets object that is constructed.
   *
   * \return Object that is constructed.
   */
  [[nodiscard]] GeometricObject* GetObject() const override;

  /**
   * \brief Gets line that is constructed.
   *
   * \return Line that is constructed.
   */
  [[nodiscard]] Line* GetLine() const;

  /**
   * Recalculate equation of line.
   */
  void RecalculateEquation() override = 0;

  void Update(const ObjectEvent::GoingToBeDestroyed& event) override;

  void Update(const ObjectEvent::Renamed& event) override;

 protected:
  ConstructionLine() = default;

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
  void SetEquation(const LineEquation& equation) const;

 private:
  std::unique_ptr<Line> line_ =
      std::make_unique<Line>();  //!< Line, which is created.
};

/**
 * \brief Construction of a casual line on a plane.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class LineOnPlane final : public ConstructionLine
{
 public:
  /**
   * \brief Constructs line by equation.
   *
   * \param equation Equation of line.
   */
  explicit LineOnPlane(LineEquation equation);

  void RecalculateEquation() override;

 private:
  LineEquation equation_;  //!< Equation of line.
};

/**
 * \brief Construction of a line by two points.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class ByTwoPoints final : public ConstructionLine, public StrongConstruction
{
 public:
  /**
   * \brief Constructs line by two points.
   *
   * \param first_point First point.
   * \param second_point Second point.
   */
  ByTwoPoints(Point* first_point, Point* second_point);

  ~ByTwoPoints() override;

  void RecalculateEquation() override;

 private:
  Point* first_point_;   //!< First point.
  Point* second_point_;  //!< Second point.
};

/**
 * \brief Base class for all conic constructions.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class ConstructionConic : public Construction
{
 public:
  /**
   * \brief Gets object that is constructed.
   *
   * \return Object that is constructed.
   */
  [[nodiscard]] GeometricObject* GetObject() const override;

  /**
   * \brief Gets conic.
   *
   * \return Contained conic.
   */
  [[nodiscard]] Conic* GetConic() const;

  /**
   * \brief Recalculate equation of conic.
   */
  void RecalculateEquation() override = 0;

  void Update(const ObjectEvent::GoingToBeDestroyed& event) override;

  void Update(const ObjectEvent::Renamed& event) override;

 protected:
  /**
   * \brief Default constructor.
   *
   */
  ConstructionConic() = default;

  /**
   * \brief Sets equation of conic.
   *
   * \param equation Equation of conic.
   */
  void SetEquation(ConicEquation equation) const;

 private:
  std::unique_ptr<Conic> conic_ =
      std::make_unique<Conic>();  //!< Conic, which is created.
};

/**
 * \brief Construction of a casual conic on a plane.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class ConicOnPlane final : public ConstructionConic, public StrongConstruction
{
 public:
  /**
   * \brief Constructs conic by equation.
   *
   * \param equation Equation of conic.
   */
  explicit ConicOnPlane(ConicEquation equation);

  void RecalculateEquation() override;

 private:
  ConicEquation equation_;  //!< Equation of conic.
};
}  // namespace HomoGebra