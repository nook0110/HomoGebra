#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <SFML/Graphics.hpp>
#include <array>
#include <complex>
#include <optional>

#include "Complex.h"

class TransformationMatrix
{
 public:
  using MatrixRow = std::array<Complex, 3>;
  using MatrixColumn = std::array<Complex, 3>;
  using MatrixContainer = std::array<std::array<Complex, 3>, 3>;

  /**
   * \brief Default Constructor. Creates identity matrix.
   *
   */
  TransformationMatrix();

  /**
   *  \brief Constructor that initializes all elements in matrix.
   *
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
   */
  explicit Transformation(
      const TransformationMatrix& transformation = TransformationMatrix());

  /**
   * \brief Construct transformation from movement of 4 points.
   *
   * \detail This transformation will do homography (preimage->image)
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
 * \brief Name of axes/variables.
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
  HomogeneousCoordinate(const Complex x, const Complex y, const Complex z)
      : x(x), y(y), z(z)
  {}

  /**
   * \brief Constructor from position on a plane.
   *
   * \param position Position on a plane.
   */
  explicit HomogeneousCoordinate(const sf::Vector2f& position)
      : x(static_cast<double>(position.x)),
        y(static_cast<double>(position.y)),
        z({1})
  {}
  /**
   * \breif Overload of operator[]. Returns const reference to x, y or z
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
   * \detail Divides on Z coordinate if it is non-zero, otherwise divides on Y
   * coordinate
   *
   * \return Reference on this object.
   */
  HomogeneousCoordinate& Normalize();

  /**
   * \brief Normalizes coordinates.
   *
   * \detail Divides on Z coordinate, if its possible, than try on Y and X
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
