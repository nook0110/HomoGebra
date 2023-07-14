#pragma once
#include "Construction.h"
#include "Equation.h"
#include "Observer.h"
class GeometricObject;

/**
 * \brief Base class for implementations of geometric objects.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 *
 * \see PointImplementation
 * \see LineImplementation
 * \see ConicImplementation
 *
 */
class GeometricObjectImplementation : public ObservableGeometricObject
{
 public:
  /**
   * \brief Destructor.
   *
   */
  ~GeometricObjectImplementation() override = default;

 private:
  std::unique_ptr<Construction> construction_;  //!< Construction of object.
};

/**
 * \brief Implementation of Point
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date April 2023
 *
 * \see Point
 */
class PointImplementation final : public GeometricObjectImplementation
{
 public:
  /**
   * \brief Construct a point with given equation.
   *
   * \param equation Equation of point.
   */
  explicit PointImplementation(PointEquation equation = PointEquation());

  /**
   * \brief Sets new equation of point.
   *
   * \param equation Equation of point.
   */
  void SetEquation(PointEquation equation);

  /**
   * \brief Return current equation of point.
   *
   * \return Point equation.
   */
  [[nodiscard]] const PointEquation& GetEquation() const;

 private:
  /**
   * Member data.
   */
  PointEquation equation_;  //!< Point equation.
};

/**
 * \brief Implementation of Line
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date April 2023
 *
 * \see Line
 */
class LineImplementation : public GeometricObjectImplementation
{
 public:
  /**
   * \brief Construct a line with given equation.
   *
   * \param equation Equation of line.
   */
  explicit LineImplementation(LineEquation equation = LineEquation());

  /**
   * \brief Sets new equation of line.
   *
   * \param equation Equation of line.
   */
  void SetEquation(LineEquation equation);

  /**
   * \brief Return equation of line.
   *
   * \return Line equation.
   */
  [[nodiscard]] const LineEquation& GetEquation() const;

 private:
  /**
   * Member data.
   */
  LineEquation equation_;  //!< Line equation.
};

/**
 * \brief Implementation of Conic
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date April 2023
 *
 * \see Conic
 */
class ConicImplementation final : public GeometricObjectImplementation
{
 public:
  /**
   * \brief Construct a conic with given equation.
   *
   * \param equation Equation of conic.
   */
  explicit ConicImplementation(ConicEquation equation = ConicEquation());

  /**
   * \brief Sets new equation of conic.
   *
   * \param equation Equation of conic.
   */
  void SetEquation(ConicEquation equation);

  /**
   * \brief Return equation of conic.
   *
   * \return Conic equation.
   */
  [[nodiscard]] const ConicEquation& GetEquation() const;

 private:
  /**
   * Member data.
   */
  ConicEquation equation_;  //!< Conic equation.
};
