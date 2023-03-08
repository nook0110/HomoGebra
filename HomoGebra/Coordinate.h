#pragma once
#include <complex>
#include <array>
#include <optional>

using complex = std::complex<long double>;

class TransformationMatrix
{
public:
  using MatrixRow = std::array<complex, 3>;
  using MatrixColumn = std::array<complex, 3>;
  using MatrixContainer = std::array<std::array<complex, 3>, 3>;

  /**
   * \brief Default Constructor. Creates identity matrix.
   *
   */
  TransformationMatrix();

  /**
   *  \brief Constructor that initializes all elements in matrix.
   *
   */
  TransformationMatrix(const complex& a00, const complex& a01, const complex& a02,
    const complex& a10, const complex& a11, const complex& a12,
    const complex& a20, const complex& a21, const complex& a22);

  /**
   * \brief Finds inversion of matrix.
   *
   * \return Inverse matrix if it exists, otherwise std::nullopt.
   */
  std::optional<TransformationMatrix> GetInverse() const;

  /**
   * \brief Calculates determinant
   *
   * \return Determinant
   */
  complex Determinant() const;

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
  TransformationMatrix operator*(const TransformationMatrix& other) const;

  const MatrixColumn& operator[](size_t row) const { return matrix_[row]; };
  MatrixColumn& operator[](size_t row) { return matrix_[row]; }

  MatrixContainer::const_iterator begin() const { return matrix_.begin(); }
  MatrixContainer::const_iterator end() const { return matrix_.end(); }
private:
  /**
   * Member data.
   */
  MatrixContainer matrix_; //!< Matrix
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
  using Row = TransformationMatrix::MatrixRow;
  using Column = TransformationMatrix::MatrixColumn;

  friend HomogeneousCoordinate operator*(const Transformation& transformation, const HomogeneousCoordinate& coordinate);

  /**
   *  \brief Constructs transformation from matrix. For default transformation use identity matrix.
   */
  explicit Transformation(const TransformationMatrix& transformation = TransformationMatrix());

  /**
   * \brief Construct transformation from movement of 4 points.
   *
   * \detail This transformation will do homography (preimage->image)
   * A projective transformation of the plane is defined by specifying four pairs of corresponding mapping points.
   * For correct homography three points of the four images or preimages shouldn't lie on the same line.
   * (Otherwise it will degenerate)
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
  Transformation(const PointEquation& first_preimage, const PointEquation& second_preimage,
    const PointEquation& third_preimage, const PointEquation& fourth_preimage,
    const PointEquation& first_image, const PointEquation& second_image,
    const PointEquation& third_image, const PointEquation& fourth_image);

  /**
   * \brief Calculate inverse of transformation.
   *
   * \return Return inverse if it exists, otherwise
   */
  std::optional<Transformation> GetInverse() const;

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
  Transformation operator*(const Transformation& other) const;

  /**
   * \brief Apply transformation to a homogeneous coordinate.
   *
   * \param coordinate A homogeneous coordinate to apply transformation on.
   * \return Coordinate after transformation
   */
  HomogeneousCoordinate operator()(const HomogeneousCoordinate& coordinate) const;

private:
  /**
   * Member data.
   */
  TransformationMatrix transformation_; //!< Matrix of transformation
};

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
 *
 */
struct HomogeneousCoordinate
{
  const complex& operator[](var variable) const;
  complex& operator[](var variable);

  complex x;
  complex y;
  complex z;
};

HomogeneousCoordinate& operator*=(HomogeneousCoordinate& coordinate, const Transformation& transformation);
HomogeneousCoordinate operator*(const Transformation& transformation, const HomogeneousCoordinate& coordinate);
