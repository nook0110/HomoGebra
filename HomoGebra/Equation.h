#pragma once
#include <complex>
#include <array>
#include <optional>
using complex = std::complex<long double>;

/**
 * \brief Coordinates in \f{ \mathbb{C}\mathrm{P}^2 \f}
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see <a href="https://en.wikipedia.org/wiki/Homogeneous_coordinates">Wikipedia: Homogeneous coordinates</a>
 */
struct HomogeneousCoordinate
{
  complex x;
  complex y;
  complex z;
};

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
   * \brief Name of axes.
   *
   */
  enum class var
  {
    kX,
    kY,
    kZ
  };
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
  * \name Equation
  * Conic equation in \f$ \mathbb {C}\mathrm {P} ^ 2 \f$ is
  * \f$ a \cdot x^2 + b \cdot y^2 + c \cdot z^2 + d \cdot yz + e \cdot xz + f \cdot xy \f$
  */
  /// @{
  std::array<complex, 3> squares;
  std::array<complex, 3> pair_products;

  /// @}

  static const std::array<var, 3> prev;
  static const std::array<var, 3> next;
};
