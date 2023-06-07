#pragma once
#include <array>

#include "Coordinate.h"

/**
 * \brief Struct that defines position of the objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 */
struct Equation
{
  /**
   * Default destructor.
   */
  virtual ~Equation() = default;

  /**
   * \brief Apply transformation to an equation.
   *
   * \param transformation Transformation to apply.
   */
  virtual void Apply(const Transformation& transformation) = 0;
};

/**
 * \brief Struct that defines position of the point.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PointImplementation
 *
 */
struct PointEquation final : public Equation
{
  /**
   * \brief Constructor.
   *
   * \param equation Equation of point.
   */
  explicit PointEquation(
      HomogeneousCoordinate equation = HomogeneousCoordinate{});

  /**
   * \brief Apply transformation to a point equation.
   *
   * \param transformation Transformation to apply.
   */
  void Apply(const Transformation& transformation) override;

  /**
   * \brief Return current equation of point.
   *
   * \return Point equation.
   */
  [[nodiscard]] HomogeneousCoordinate& GetEquation();

  /**
   * \brief Return current equation of point.
   *
   * \return Point equation.
   */
  [[nodiscard]] const HomogeneousCoordinate& GetEquation() const;

  HomogeneousCoordinate equation;  //!< Equation of point.
};

/**
 * \brief Struct that defines position of the line
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see LineImplementation
 *
 */
struct LineEquation final : public Equation
{
  /**
   * \brief Constructor.
   *
   * \param equation Equation of line.
   */
  explicit LineEquation(
      HomogeneousCoordinate equation = HomogeneousCoordinate{});

  /**
   * \brief Apply transformation to a conic equation.
   *
   * \warning It will multiply on inverse of transformation. Because if you
   * substitute an image of point, equation should equal to zero.
   *
   * \param transformation Transformation to apply.
   */
  void Apply(const Transformation& transformation) override;

  HomogeneousCoordinate equation;  //!< Equation of line
};

/**
 * \brief Struct that defines position of the conic
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see ConicImplementation
 *
 */
struct ConicEquation final : public Equation
{
  /**
   * \name Static arrays to get next o previous vars.
   *
   * It is used to get from Equation::Var next or previous Equation::Var
   */

  /// @{
  static constexpr std::array<Var, 3> kPrev = {Var::kZ, Var::kX,
                                               Var::kY};  //!< Previous var
  static constexpr std::array<Var, 3> kNext = {Var::kY, Var::kZ,
                                               Var::kX};  //!< Next var
  /// @}

  /**
   * \brief Apply transformation to a conic equation.
   *
   * \warning This method is not implemented!
   *
   * \param transformation Transformation to apply.
   */
  void Apply(const Transformation& transformation) override;

  /**
   * \name Equation
   *
   * Conic equation in \f$ \mathbb {C}\mathrm {P} ^ 2 \f$ is
   * \f$ a \cdot x^2 + b \cdot y^2 + c \cdot z^2 + d \cdot yz + e \cdot xz + f
   * \cdot xy \f$
   */
  /// @{
  std::array<Complex, 3> squares;        //!< \f$ a, b, c \f$
  std::array<Complex, 3> pair_products;  //!< \f$ d, e, f \f$
  /// @}
};
