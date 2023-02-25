#pragma once
#include <array>
#include <optional>

#include "Coordinate.h"

/**
 * \brief Struct that defines position of the objects
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
   * \param transformation
   */
  virtual void Apply(const Transformation& transformation) = 0;
};

/**
 * \brief Struct that defines position of the point
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PointImplementataion
 *
 */
struct PointEquation : public Equation
{
  explicit PointEquation(const HomogeneousCoordinate& equation);
  /**
   * \brief Apply transformation to a point equation.
   *
   * \param transformation
   */
  void Apply(const Transformation& transformation) override;

  HomogeneousCoordinate& GetEquation();
  const HomogeneousCoordinate& GetEquation() const;

  HomogeneousCoordinate equation;
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
 * \see LineImplementataion
 *
 */
struct LineEquation : public Equation
{
  /**
   * \brief Apply transformation to a conic equation.
   *
   * \warning It will multiply on inverse of transformation. Because if you substitute an image of point, equation should equal to zero.
   *
   * \param transformation
   */
  void Apply(const Transformation& transformation) override;

  HomogeneousCoordinate equation;
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
 * \see ConicImplementataion
 *
 */
struct ConicEquation : public Equation
{
  /**
   * \name Static arrays to get next o previous vars.
   *
   * It is used to get from Equation::var next or previous Equation::var
   */

  /// @{
  
  static const std::array<var, 3> prev;
  static const std::array<var, 3> next;

  /// @}

  /**
   * \brief Apply transformation to a conic equation.
   *
   * \warning It will multiply on inverse of transformation squared each element. Because if you substitute an image of point, equation should equal to zero.
   *
   * \param transformation
   */
  void Apply(const Transformation& transformation) override;

  /**
  * \name Equation
  *
  * Conic equation in \f$ \mathbb {C}\mathrm {P} ^ 2 \f$ is
  * \f$ a \cdot x^2 + b \cdot y^2 + c \cdot z^2 + d \cdot yz + e \cdot xz + f \cdot xy \f$
  */
  /// @{
  
  std::array<complex, 3> squares;
  std::array<complex, 3> pair_products;

  /// @}
};
