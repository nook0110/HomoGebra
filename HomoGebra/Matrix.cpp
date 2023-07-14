#include "Matrix.h"

#include <algorithm>
#include <iostream>

#include "Assert.h"

template <typename UnderlyingType>
SquaredMatrix<UnderlyingType>::SquaredMatrix(const size_t size)
    : matrix_(size, Row(size)), augmentation_(size), size_(size)
{}

template <typename UnderlyingType>
SquaredMatrix<UnderlyingType>::SquaredMatrix(const Matrix& matrix,
                                             const Row& augmentation)
    : matrix_(matrix), augmentation_(augmentation), size_(matrix.size())
{
  // Check if matrix is squared
  Assert(!(std::any_of(matrix.begin(), matrix.end(),
                       [this](const Row& row) { return row.size() != size_; })),
         "Matrix is not squared!");

  // Check if augmentation is correct
  Assert(augmentation.size() == size_, "Augmentation size is incorrect!");
}

template <typename UnderlyingType>
std::optional<SquaredMatrix<UnderlyingType>>
SquaredMatrix<UnderlyingType>::GetInverse() const
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
    const UnderlyingType pivot_value = matrix[step][step];
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
        UnderlyingType multiplier = matrix[row][step];

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

template <typename UnderlyingType>
UnderlyingType SquaredMatrix<UnderlyingType>::GetDeterminant() const
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
        UnderlyingType multiplier = matrix[row][step] / matrix[step][step];

        for (size_t column = 0; column < size_; ++column)
        {
          matrix[row][column] -= matrix[step][column] * multiplier;
        }
      }
    }
  }

  // Calculate determinant
  UnderlyingType determinant = 1;
  for (size_t i = 0; i < size_; ++i)
  {
    determinant *= matrix[i][i];
  }

  // Return answer
  return determinant;
}

template <typename UnderlyingType>
typename std::optional<typename SquaredMatrix<UnderlyingType>::Column>
SquaredMatrix<UnderlyingType>::GetSolution() const
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

template <typename UnderlyingType>
size_t SquaredMatrix<UnderlyingType>::GetSize() const
{
  return size_;
}

template <typename UnderlyingType>
typename SquaredMatrix<UnderlyingType>::Column&
SquaredMatrix<UnderlyingType>::GetAugmentation()
{
  return augmentation_;
}

template <typename UnderlyingType>
const typename SquaredMatrix<UnderlyingType>::Column&
SquaredMatrix<UnderlyingType>::GetAugmentation() const
{
  return augmentation_;
}

template <typename UnderlyingType>
SquaredMatrix<UnderlyingType>& SquaredMatrix<UnderlyingType>::operator*=(
    const SquaredMatrix& other)
{
  (*this) = (*this) * other;

  return *this;
}

template <typename UnderlyingType>
SquaredMatrix<UnderlyingType> SquaredMatrix<UnderlyingType>::operator*(
    const SquaredMatrix& other) const
{
  // Check if matrices are compatible
  Assert(size_ != other.size_, "Matrices sizes are different!");

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

template <typename UnderlyingType>
std::vector<UnderlyingType> SquaredMatrix<UnderlyingType>::operator*(
    const std::vector<UnderlyingType>& vector) const
{
  // Check if vector is compatible
  Assert(vector.size() != size_, "Vector size is incorrect!");

  // Construct new vector filled with zeros
  std::vector<UnderlyingType> result(size_);

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

template <typename UnderlyingType>
typename SquaredMatrix<UnderlyingType>::Row&
SquaredMatrix<UnderlyingType>::operator[](const size_t row)
{
  return matrix_[row];
}

template <typename UnderlyingType>
const typename SquaredMatrix<UnderlyingType>::Row&
SquaredMatrix<UnderlyingType>::operator[](const size_t row) const
{
  return matrix_[row];
}

template <typename UnderlyingType>
typename SquaredMatrix<UnderlyingType>::Matrix::const_iterator
SquaredMatrix<UnderlyingType>::begin() const
{
  // Return iterator to first row
  return matrix_.begin();
}

template <typename UnderlyingType>
typename SquaredMatrix<UnderlyingType>::Matrix::const_iterator
SquaredMatrix<UnderlyingType>::end() const
{
  // Return iterator to last row
  return matrix_.end();
}

/**
 * \brief Explicit template specialization for complex numbers
 *
 * \param value Value to check
 *
 * \return True if value is zero, false otherwise
 */
template <>
bool SquaredMatrix<Complex>::IsZero(const Complex& value) const
{
  return value.IsZero();
}

/**
 * \brief Explicit template specialization for float numbers
 *
 * \param value Value to check
 *
 * \return True if value is zero, false otherwise
 */
template <>
bool SquaredMatrix<float>::IsZero(const float& value) const
{
  return Complex{value}.IsZero();
}

template class SquaredMatrix<Complex>;
template class SquaredMatrix<float>;