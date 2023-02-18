#pragma once
#include <complex>
#include <vector>
#include <optional>

using complex = std::complex<long double>;

/**
 * \brief A squared matrix with augmentation.
 */
class SquaredMatrix
{
public:
  /**
   * \brief Type aliases.
   *
   */
  using Row = std::vector<complex>;
  using Column = std::vector<complex>;
  using Matrix = std::vector<Row>;

  /**
   * \brief Construct from size. Matrix and augmentation will be filled with zeros.
   *
   * \param size Size of matrix
   */
  explicit SquaredMatrix(size_t size);

  /**
   * \brief Constructor that initializes all elements in matrix and its augmentation
   *
   * \param matrix Matrix
   * \param augmentation Augmentation
   */
  SquaredMatrix(const Matrix& matrix, const Row& augmentation);

  /**
   * \brief Finds inversion of matrix.
   *
   * \return Inverse matrix if it exists, otherwise std::nullopt.
   */
  std::optional<SquaredMatrix> GetInverse() const;

  /**
   * \brief Calculates determinant
   *
   * \return Determinant
   */
  complex Determinant() const;

  /**
   * \brief Find solution of linear equations.
   *
   * \return Vector of solutions
   */
  std::optional<Column> GetSolution() const;

  /**
   * \brief Get size of matrix.
   *
   * \return size of matrix
   */
  size_t GetSize() const;

  /**
   * \brief Get matrix augmentation.
   *
   * \return augmentation
   */
  Column GetAugmentation() const;

  /**
   * \brief Multiplies this matrix on another one.
   *
   * \param other Another matrix
   * \return Reference to this object
   */
  SquaredMatrix& operator*=(const SquaredMatrix& other);

  /**
   * \brief Multiplies this matrix on another one.
   *
   * \param other Another matrix
   * \return New matrix equals to result of multiplication
   */
  SquaredMatrix operator*(const SquaredMatrix& other) const;

  /**
   * \brief Multiplies this matrix on vector.
   *
   * \param vector Vector
   * \return New vector equals to result of multiplication
   */
  std::vector<complex> operator*(const std::vector<complex>& vector) const;

  /**
   * \brief operator to get row of matrix.
   *
   * \param row Row of matrix
   */
  Row& operator[](size_t row);

  /**
  * \brief operator to get row of matrix.
  *
  * \param row Row of matrix
  */
  const Row& operator[](size_t row) const;

private:

  static const long double kEpsilon; //<! Epsilon for comparison

  /**
 * Default constructor.
 */
  SquaredMatrix() = default;

  /**
   * Member data.
   */

  Matrix matrix_; //<! Matrix
  Column augmentation_; //<! Augmentation

  size_t size_; //<! Size of matrix

};




