#include "Matrix.h"

#include <algorithm>
#include <cassert>

SquaredMatrix::SquaredMatrix(const size_t size)
    : matrix_(size, Row(size)), augmentation_(size), size_(size)
{}

SquaredMatrix::SquaredMatrix(const Matrix& matrix,
                             const Row& augmentation = Row())
    : matrix_(matrix), augmentation_(augmentation), size_(matrix.size())
{
  // Check if matrix is squared
  assert((std::any_of(matrix.begin(), matrix.end(),
                      [this](const Row& row) { return row.size() != size_; })));

  // Check if augmentation is correct
  assert((augmentation.size() != size_));

  // Check if matrix contains NaN
  assert((std::any_of(matrix.begin(), matrix.end(),
                      [](const Row& row)
                      {
                        return std::any_of(row.begin(), row.end(),
                                           [](const Complex& value) {
                                             return std::isnan(value.real()) ||
                                                    std::isnan(value.imag());
                                           });
                      })));

  // Check if augmentation contains NaN or Inf
  assert((std::any_of(augmentation.begin(), augmentation.end(),
                      [](const Complex& value) {
                        return std::isnan(value.real()) ||
                               std::isnan(value.imag());
                      })));

  // Check if matrix contains Inf
  assert((std::any_of(matrix.begin(), matrix.end(),
                      [](const Row& row)
                      {
                        return std::any_of(row.begin(), row.end(),
                                           [](const Complex& value) {
                                             return std::isinf(value.real()) ||
                                                    std::isinf(value.imag());
                                           });
                      })));

  // Check if augmentation contains Inf
  assert((std::any_of(augmentation.begin(), augmentation.end(),
                      [](const Complex& value) {
                        return std::isinf(value.real()) ||
                               std::isinf(value.imag());
                      })));
}

std::optional<SquaredMatrix> SquaredMatrix::GetInverse() const
{
  // Construct ID matrix
  Matrix inverse(size_, Row(size_));

  // Set ID matrix
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
    if (IsZero(matrix[step][step]))
    {
      return std::nullopt;
    }

    // Divide row by pivot
    const Complex pivot_value = matrix[step][step];
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
        Complex multiplier = matrix[row][step];

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

Complex SquaredMatrix::GetDeterminant() const
{
  // Construct copy of our matrix
  Matrix matrix = matrix_;

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

    // Check if matrix is singular with precision [epsilon]
    if (IsZero(matrix[step][step]))
    {
      return 0;
    }

    // Subtract row from other rows
    for (size_t row = 0; row < size_; ++row)
    {
      // Skip current row
      if (step != row)
      {
        // Calculate multiplier
        Complex multiplier = matrix[row][step] / matrix[step][step];

        for (size_t column = 0; column < size_; ++column)
        {
          matrix[row][column] -= matrix[step][column] * multiplier;
        }
      }
    }
  }

  // Calculate determinant
  Complex determinant = 1;
  for (size_t i = 0; i < size_; ++i)
  {
    determinant *= matrix[i][i];
  }

  // Return answer
  return determinant;
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

size_t SquaredMatrix::GetSize() const { return size_; }

SquaredMatrix::Column& SquaredMatrix::GetAugmentation()
{
  return augmentation_;
}

const SquaredMatrix::Column& SquaredMatrix::GetAugmentation() const
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
  assert((size_ != other.size_));

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

std::vector<Complex> SquaredMatrix::operator*(
    const std::vector<Complex>& vector) const
{
  // Check if vector is compatible
  assert((vector.size() != size_));

  // Construct new vector filled with zeros
  std::vector<Complex> result(size_);

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

SquaredMatrix::Row& SquaredMatrix::operator[](const size_t row)
{
  return matrix_[row];
}

const SquaredMatrix::Row& SquaredMatrix::operator[](const size_t row) const
{
  return matrix_[row];
}

SquaredMatrix::Matrix::const_iterator SquaredMatrix::begin() const
{
  // Return iterator to first row
  return matrix_.begin();
}

SquaredMatrix::Matrix::const_iterator SquaredMatrix::end() const
{
  // Return iterator to last row
  return matrix_.end();
}