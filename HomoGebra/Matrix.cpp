#include "Matrix.h"
#include <algorithm>

// Static member init
const long double SquaredMatrix::kEpsilon = 1e-12L;

SquaredMatrix::SquaredMatrix(size_t size)
  : matrix_(size, Row(size))
  , augmentation_(size),
  size_(size)
{}

SquaredMatrix::SquaredMatrix(const Matrix& matrix, const Row& augmentation = Row())
  :matrix_(matrix), augmentation_(augmentation), size_(matrix.size())
{
  if (std::any_of(matrix.begin(), matrix.end(),
                  [this](const Row& row) { return row.size() != size_; }))
  {
    throw std::invalid_argument("Matrix is not squared");
  }

  if (augmentation.size() != size_)
  {
    throw std::invalid_argument("Augmentation is not correct");
  }

  if (std::any_of(matrix.begin(), matrix.end(),
                  [](const Row& row) { return std::any_of(row.begin(), row.end(), [](const complex& value) { return std::isnan(value.real()) || std::isnan(value.imag()); }); }))
  {
    throw std::invalid_argument("Matrix contains NaN");
  }

  if (std::any_of(augmentation.begin(), augmentation.end(), [](const complex& value) { return std::isnan(value.real()) || std::isnan(value.imag()); }))
  {
    throw std::invalid_argument("Augmentation contains NaN");
  }

  if (std::any_of(matrix.begin(), matrix.end(),
                  [](const Row& row) { return std::any_of(row.begin(), row.end(), [](const complex& value) { return std::isinf(value.real()) || std::isinf(value.imag()); }); }))
  {
    throw std::invalid_argument("Matrix contains Inf");
  }

  if (std::any_of(augmentation.begin(), augmentation.end(), [](const complex& value) { return std::isinf(value.real()) || std::isinf(value.imag()); }))
  {
    throw std::invalid_argument("Augmentation contains Inf");
  }
}

std::optional<SquaredMatrix> SquaredMatrix::GetInverse() const
{
  // Construct ID matrix
  Matrix inverse(size_, Row(size_));

  for (size_t i = 0; i < size_; ++i)
  {
    inverse[i][i] = 1;
  }

  // Construct inverse augmentation
  Row inverse_augmentation(size_);

  // Construct copy of our matrix
  Matrix matrix = matrix_;

  // Construct copy of augmentation
  Column augmentation = augmentation_;

  // Gauss-Jordan elimination for matrix and augmentation
  for (size_t step = 0; step < size_; ++step)
  {
    // Find pivot
    size_t pivot = step;
    for (size_t row = step + 1; row < size_; ++row)
    {
      if (std::abs(matrix[row][step]) > std::abs(matrix[pivot][step]))
      {
        pivot = row;
      }
    }

    // Swap rows
    std::swap(matrix[step], matrix[pivot]);
    std::swap(inverse[step], inverse[pivot]);
    std::swap(augmentation[step], augmentation[pivot]);
    std::swap(inverse_augmentation[step], inverse_augmentation[pivot]);

    // Check if matrix is singular with precision [epsilon]
    if (std::abs(matrix[step][step]) < kEpsilon)
    {
      return std::nullopt;
    }

    // Divide row by pivot
    complex pivot_value = matrix[step][step];
    for (size_t column = 0; column < size_; ++column)
    {
      matrix[step][column] /= pivot_value;
      inverse[step][column] /= pivot_value;
    }

    augmentation[step] /= pivot_value;
    inverse_augmentation[step] /= pivot_value;

    // Subtract row from other rows
    for (size_t row = 0; row < size_; ++row)
    {
      // Skip current row
      if (step != row)
      {
        complex multiplier = matrix[row][step];

        for (size_t column = 0; column < size_; ++column)
        {
          matrix[row][column] -= matrix[step][column] * multiplier;
          inverse[row][column] -= inverse[step][column] * multiplier;
        }

        augmentation[row] -= augmentation[step] * multiplier;
        inverse_augmentation[row] -= inverse_augmentation[step] * multiplier;
      }
    }
  }

  // Return answer
  return SquaredMatrix(inverse, augmentation);
}

complex SquaredMatrix::Determinant() const
{
  return complex();
}

std::optional<SquaredMatrix::Column> SquaredMatrix::GetSolution() const
{
  // Find inverse
  auto inverse = GetInverse();

  // Check if matrix is singular
  if (!inverse)
  {
    return std::nullopt;
  }

  // Return solution
  return inverse->GetAugmentation();
}

size_t SquaredMatrix::GetSize() const
{
  return size_;
}

SquaredMatrix::Column SquaredMatrix::GetAugmentation() const
{
  return augmentation_;
}

SquaredMatrix& SquaredMatrix::operator*=(const SquaredMatrix& other)
{
  (*this) = (*this) * other;

  return *this;
}

SquaredMatrix SquaredMatrix::operator*(const SquaredMatrix& other) const
{
  // Check if matrices are compatible
  if (size_ != other.size_)
  {
    throw std::invalid_argument("Matrices are not compatible");
  }

  // Construct new matrix filled with zeros
  SquaredMatrix result(size_);

  // Multiply matrices
  for (size_t i = 0; i < size_; ++i)
  {
    for (size_t j = 0; j < size_; ++j)
    {
      for (size_t k = 0; k < size_; ++k)
      {
        result[i][j] += matrix_[i][k] * other[k][j];
      }
    }
  }

  // Return result
  return result;
}

std::vector<complex> SquaredMatrix::operator*(const std::vector<complex>& vector) const
{
  // Check if vector is compatible
  if (vector.size() != size_)
  {
    throw std::invalid_argument("Vector is not compatible");
  }

  // Construct new vector filled with zeros
  std::vector<complex> result(size_);

  // Multiply
  for (size_t i = 0; i < size_; ++i)
  {
    for (size_t j = 0; j < size_; ++j)
    {
      result[i] += matrix_[i][j] * vector[j];
    }
  }

  // Return result
  return result;
}

SquaredMatrix::Row& SquaredMatrix::operator[](size_t row)
{
  return matrix_[row];
}

const SquaredMatrix::Row& SquaredMatrix::operator[](size_t row) const
{
  return matrix_[row];
}
