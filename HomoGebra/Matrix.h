#pragma once
#include <complex>
#include <optional>
#include <vector>

#include "Complex.h"

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
  using Row = std::vector<Complex>;     //!< Row of matrix
  using Column = std::vector<Complex>;  //!< Column of matrix
  using Matrix = std::vector<Row>;      //!< Matrix

  /**
   * \brief Construct from size. Matrix and augmentation will be filled with
   * zeros.
   *
   * \param size Size of matrix
   */
  explicit SquaredMatrix(const size_t size);

  /**
   * \brief Constructor that initializes all elements in matrix and its
   * augmentation
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
  [[nodiscard]] std::optional<SquaredMatrix> GetInverse() const;

  /**
   * \brief Calculates determinant
   *
   * \return Determinant
   */
  [[nodiscard]] Complex GetDeterminant() const;

  /**
   * \brief Find solution of linear equations.
   *
   * \return Vector of solutions
   */
  [[nodiscard]] std::optional<Column> GetSolution() const;

  /**
   * \brief Get size of matrix.
   *
   * \return size of matrix
   */
  [[nodiscard]] size_t GetSize() const;

  /**
   * \brief Get matrix augmentation.
   *
   * \return augmentation
   */
  [[nodiscard]] Column& GetAugmentation();

  /**
   * \brief Get matrix augmentation.
   *
   * \return augmentation
   */
  [[nodiscard]] const Column& GetAugmentation() const;

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
  [[nodiscard]] SquaredMatrix operator*(const SquaredMatrix& other) const;

  /**
   * \brief Multiplies this matrix on vector.
   *
   * \param vector Vector
   * \return New vector equals to result of multiplication
   */
  [[nodiscard]] std::vector<Complex> operator*(
      const std::vector<Complex>& vector) const;

  /**
   * \brief operator to get row of matrix.
   *
   * \param row Row of matrix
   *
   * \return Row of matrix
   */
  [[nodiscard]] Row& operator[](const size_t row);

  /**
   * \brief operator to get row of matrix.
   *
   * \param row Row of matrix
   *
   * \return Row of matrix
   */
  [[nodiscard]] const Row& operator[](const size_t row) const;

  /**
   * \brief Return iterator to the beginning of rows
   *
   * \return Iterator to first row
   */
  [[nodiscard]] Matrix::const_iterator begin() const;

  /**
   * \brief Return iterator to the end of rows
   *
   * \return Iterator to end of rows
   */
  [[nodiscard]] Matrix::const_iterator end() const;

 private:
  /**
   * Default constructor.
   */
  SquaredMatrix() = default;

  /**
   * Member data.
   */

  Matrix matrix_{};        //!< Matrix
  Column augmentation_{};  //!< Augmentation
  size_t size_{};          //!< Size of matrix
};
