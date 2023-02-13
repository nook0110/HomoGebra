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
   * \brief Default Constructor.
   *
   */
  TransformationMatrix();

  /**
   *  \brief Constructor that initializes all elements in matrix
   *
   */
  TransformationMatrix(const complex& a00, const complex& a01, const complex& a02,
                       const complex& a10, const complex& a11, const complex& a12,
                       const complex& a20, const complex& a21, const complex& a22);

  /**
   * Finds inversion of matrix.
   *
   * \return Inverse matrix
   */
  std::optional<TransformationMatrix> GetInverse() const;

  /**
   * Calculates determinant
   *
   * \return Determinant
   */
  complex Determinant() const;

  /**
   * Multiplies this matrix on another one.
   *
   * \param other Another matrix
   * \return Reference to this object
   */
  TransformationMatrix& operator*=(const TransformationMatrix& other);

  /**
   * Multiplies this matrix on another one.
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
  MatrixContainer matrix_;
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
 */
struct HomogeneousCoordinate
{
  complex x;
  complex y;
  complex z;
};

struct PointEquation;

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
  /**
   *  \brief Constructs transformation from matrix.
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

  std::optional<Transformation> GetInverse() const;
private:
  TransformationMatrix transformation_;
};
