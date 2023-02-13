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
   * Default Constructor.
   * 
   */
  TransformationMatrix();

  /**
   * Constructor that initializes all elements in matrix
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

class Transformation
{
public:
  Transformation(const TransformationMatrix& transformation = TransformationMatrix());

private:
  TransformationMatrix transformation_;
};


