#include "Coordinate.h"
#include <optional>

TransformationMatrix::TransformationMatrix()
{
  // Make Identity matrix
  for (int iter = 0; iter < std::tuple_size<MatrixColumn>::value; ++iter)
  {
    matrix_[iter][iter] = complex(1, 0);
  }
}

TransformationMatrix::TransformationMatrix(const complex& a00, const complex& a01, const complex& a02,
                                           const complex& a10, const complex& a11, const complex& a12,
                                           const complex& a20, const complex& a21, const complex& a22)
  :matrix_(MatrixContainer {
          MatrixRow{a00,a01,a02},
          MatrixRow{a10,a11,a12},
          MatrixRow{a20,a21,a22}
           }
  )
{}

std::optional<TransformationMatrix> TransformationMatrix::GetInverse() const
{
  // Compute the determinant
  auto det = Determinant();

  // Compute the inverse if the determinant is not zero
  if (det == complex { 0 })
    return std::nullopt;

  return TransformationMatrix(
    (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) / det,
    -(matrix_[0][1] * matrix_[2][2] - matrix_[0][2] * matrix_[2][1]) / det,
    (matrix_[0][1] * matrix_[1][2] - matrix_[0][2] * matrix_[1][1]) / det,

    -(matrix_[1][0] * matrix_[2][2] - matrix_[1][2] * matrix_[2][0]) / det,
    (matrix_[0][0] * matrix_[2][2] - matrix_[0][2] * matrix_[2][0]) / det,
    -(matrix_[0][0] * matrix_[1][2] - matrix_[0][2] * matrix_[1][0]) / det,

    (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]) / det,
    -(matrix_[0][0] * matrix_[2][1] - matrix_[0][1] * matrix_[2][0]) / det,
    (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]) / det
  );
}

complex TransformationMatrix::Determinant() const
{
  // Compute the determinant
  return matrix_[0][0] * (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) -
    matrix_[0][1] * (matrix_[1][0] * matrix_[2][2] - matrix_[1][2] * matrix_[2][0]) +
    matrix_[0][2] * (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]);
}

TransformationMatrix& TransformationMatrix::operator*=(const TransformationMatrix& other)
{
  // Assigning multiplication result to this
  (*this) = (*this) * other;

  // Returning this
  return *this;
}

TransformationMatrix TransformationMatrix::operator*(const TransformationMatrix& other) const
{
  // Matrix that we will return (this*other)
  TransformationMatrix product_matrix;

  // Iterating through all elements in matrix
  for (int row = 0; row < std::tuple_size<MatrixColumn>::value; ++row)
  {
    for (int column = 0; column < std::tuple_size<MatrixRow>::value; ++column)
    {
      // Multiplication of row [this] and column [other]
      complex sum = 0;

      // Element-by-element multiplication
      for (int it = 0; it < std::tuple_size<MatrixRow>::value; ++it)
      {
        sum += matrix_[row][it] * other[it][column];
      }

      // Setting element
      product_matrix[row][column] = sum;
    }
  }

  // Return answer
  return product_matrix;
}

Transformation::Transformation(const TransformationMatrix& transformation)
  :transformation_(transformation)
{}

std::optional<Transformation> Transformation::GetInverse() const
{
  // Return inverse transformation
  return std::optional<Transformation>(transformation_.GetInverse());
}