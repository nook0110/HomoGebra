#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <array>
#include <complex>
#include <optional>

#include "Complex.h"

/**
 * \brief A 3x3 matrix.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class TransformationMatrix
{
 public:
  using MatrixRow = std::array<Complex, 3>;     //!< Row of matrix.
  using MatrixColumn = std::array<Complex, 3>;  //!< Column of matrix.
  using MatrixContainer =
      std::array<std::array<Complex, 3>, 3>;  //!< Container of matrix.

  /**
   * \brief Default Constructor. Creates identity matrix.
   *
   */
  TransformationMatrix();

  /**
   *  \brief Constructor that initializes all elements in matrix.
   *
   * \param a00 First element of matrix (0,0)
   * \param a01 Second element of matrix (0,1)
   * \param a02 Third element of matrix (0,2)
   * \param a10 Fourth element of matrix (1,0)
   * \param a11 Fifth element of matrix (1,1)
   * \param a12 Sixth element of matrix (1,2)
   * \param a20 Seventh element of matrix (2,0)
   * \param a21 Eighth element of matrix (2,1)
   * \param a22 Ninth element of matrix (2,2)
   */
  TransformationMatrix(const Complex& a00, const Complex& a01,
                       const Complex& a02, const Complex& a10,
                       const Complex& a11, const Complex& a12,
                       const Complex& a20, const Complex& a21,
                       const Complex& a22);

  /**
   * \brief Finds inversion of matrix.
   *
   * \return Inverse matrix if it exists, otherwise std::nullopt.
   */
  [[nodiscard]] std::optional<TransformationMatrix> GetInverse() const;

  /**
   * \brief Calculates determinant
   *
   * \return Determinant
   */
  [[nodiscard]] Complex Determinant() const;

  /**
   * \brief Multiplies this matrix on another one.
   *
   * \param other Another matrix
   * \return Reference to this object
   */
  TransformationMatrix& operator*=(const TransformationMatrix& other);

  /**
   * \brief Multiplies this matrix on another one.
   *
   * \param other Another matrix
   * \return New matrix equals to result of multiplication
   */
  [[nodiscard]] TransformationMatrix operator*(
      const TransformationMatrix& other) const;

  /**
   * \brief Overload of operator[]. Returns row of matrix.
   *
   * \param row Row of matrix
   *
   * \return Row of matrix
   */
  [[nodiscard]] const MatrixRow& operator[](size_t row) const;

  /**
   * \brief Overload of operator[]. Returns row of matrix.
   *
   * \param row Row of matrix
   *
   * \return Row of matrix
   */
  [[nodiscard]] MatrixRow& operator[](size_t row);

  /**
   * \brief Get iterator to the beginning of matrix.
   *
   * \return Iterator to the beginning of matrix
   */
  [[nodiscard]] MatrixContainer::const_iterator begin() const;

  /**
   * \brief Get iterator to the end of matrix.
   *
   * \return Iterator to the end of matrix
   */
  [[nodiscard]] MatrixContainer::const_iterator end() const;

 private:
  /**
   * Member data.
   */
  MatrixContainer matrix_;  //!< Matrix
};

struct PointEquation;
struct HomogeneousCoordinate;

/**
 * \brief Class to save and do homography.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 */
class Transformation
{
 public:
  using Row = TransformationMatrix::MatrixRow;        //!< Row of matrix
  using Column = TransformationMatrix::MatrixColumn;  //!< Column of matrix

  friend HomogeneousCoordinate operator*(
      const Transformation& transformation,
      const HomogeneousCoordinate& coordinate);

  /**
   *  \brief Constructs transformation from matrix. For default transformation
   * use identity matrix.
   *
   * \param transformation Matrix of transformation
   */
  explicit Transformation(
      const TransformationMatrix& transformation = TransformationMatrix());

  /**
   * \brief Construct transformation from movement of 4 points.
   *
   * \details This transformation will do homography (preimage->image)
   * A projective transformation of the plane is defined by specifying four
   * pairs of corresponding mapping points. For correct homography three points
   * of the four images or preimages should not lie on the same line. (Otherwise
   * it will degenerate)
   *
   * \param first_preimage First point preimage position
   * \param second_preimage Second point preimage position
   * \param third_preimage Third point preimage position
   * \param fourth_preimage Fourth point preimage position
   * \param first_image First point image position
   * \param second_image Second point preimage position
   * \param third_image Third point preimage position
   * \param fourth_image Fourth point preimage position
   */
  Transformation(
      const PointEquation& first_preimage, const PointEquation& second_preimage,
      const PointEquation& third_preimage, const PointEquation& fourth_preimage,
      const PointEquation& first_image, const PointEquation& second_image,
      const PointEquation& third_image, const PointEquation& fourth_image);

  /**
   * \brief Calculate inverse of transformation.
   *
   * \return Return inverse if it exists, otherwise
   */
  [[nodiscard]] std::optional<Transformation> GetInverse() const;

  /**
   * \brief Apply transformation to this.
   *
   * \param other Which transformation to apply.
   * \return Reference to this transformation.
   */
  Transformation& operator*=(const Transformation& other);

  /**
   * \brief Combine two transformations.
   *
   * \param other Which transformation to apply.
   * \return A combined transformation
   */
  [[nodiscard]] Transformation operator*(const Transformation& other) const;

  /**
   * \brief Apply transformation to a homogeneous coordinate.
   *
   * \param coordinate A homogeneous coordinate to apply transformation on.
   * \return Coordinate after transformation
   */
  [[nodiscard]] HomogeneousCoordinate operator()(
      const HomogeneousCoordinate& coordinate) const;

 private:
  /**
   * Member data.
   */
  TransformationMatrix transformation_;  //!< Matrix of transformation
};

/**
 * \enum Var NameSaver of axes/variables.
 *
 * \var Var::kX
 * X axis
 *
 * \var Var::kY
 * Y axis
 *
 * \var Var::kZ
 * Z axis
 */
enum class Var
{
  kX,
  kY,
  kZ
};

/**
 * \brief Coordinates in \f$ \mathbb{C}\mathrm{P}^2 \f$
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see <a>
 * href="https://en.wikipedia.org/wiki/Homogeneous_coordinates">Wikipedia:
 * Homogeneous coordinates</a>
 *
 */
struct HomogeneousCoordinate
{
  /**
   * \brief Default constructor.
   *
   */
  HomogeneousCoordinate() = default;

  /**
   * \brief Constructor like list-initialization.
   *
   * \param x X coordinate
   * \param y Y coordinate
   * \param z Z coordinate
   */
  HomogeneousCoordinate(const Complex x, const Complex y, const Complex z = 1)
      : x(x), y(y), z(z)
  {}

  /**
   * \brief Overload of operator[]. Returns const reference to x, y or z
   * coordinate.
   *
   * \param variable Variable to get reference to
   *
   * \return Returns const reference to x, y or z coordinate.
   */
  [[nodiscard]] const Complex& operator[](const Var variable) const;

  /**
   * \brief Overload of operator[]. Returns reference to x, y or z coordinate.
   *
   * \param variable Variable to get reference to
   *
   * \return Returns reference to x, y or z coordinate.
   */
  [[nodiscard]] Complex& operator[](const Var variable);

  /**
   * \brief Normalizes coordinates.
   *
   * \details Divides on Z coordinate if it is non-zero, otherwise divides on Y
   * coordinate
   *
   * \return Reference on this object.
   */
  HomogeneousCoordinate& Normalize();

  /**
   * \brief Normalizes coordinates.
   *
   * \details Divides on Z coordinate, if its possible, than try on Y and X
   *
   * \return Gets normalized coordinates.
   */
  [[nodiscard]] HomogeneousCoordinate GetNormalized() const;

  Complex x;  //!< X coordinate
  Complex y;  //!< Y coordinate
  Complex z;  //!< Z coordinate
};

/**
 * \brief Overload of operator *= for homogeneous coordinate and transformation.
 * Transforms coordinate.
 *
 * \param coordinate Coordinate to transform
 * \param transformation Transformation to apply
 *
 * \return Reference to a coordinate
 */
HomogeneousCoordinate& operator*=(HomogeneousCoordinate& coordinate,
                                  const Transformation& transformation);

/**
 * \brief Overload of operator * for homogeneous coordinate and transformation.
 * Transforms coordinate.
 *
 * \param coordinate Coordinate to transform
 * \param transformation Transformation to apply
 *
 * \return Coordinate after transformation
 */
[[nodiscard]] HomogeneousCoordinate operator*(
    const Transformation& transformation,
    const HomogeneousCoordinate& coordinate);
