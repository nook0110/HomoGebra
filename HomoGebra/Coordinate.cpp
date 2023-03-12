#include "Coordinate.h"

#include <optional>

#include "Equation.h"
#include "Matrix.h"

TransformationMatrix::TransformationMatrix()
{
  // Make Identity matrix
  for (int iter = 0; iter < std::tuple_size<MatrixColumn>::value; ++iter)
  {
    // Set diagonal to 1
    matrix_[iter][iter] = complex{1};
  }
}

TransformationMatrix::TransformationMatrix(
    const complex& a00, const complex& a01, const complex& a02,
    const complex& a10, const complex& a11, const complex& a12,
    const complex& a20, const complex& a21, const complex& a22)
    : matrix_(MatrixContainer{MatrixRow{a00, a01, a02},
                              MatrixRow{a10, a11, a12},
                              MatrixRow{a20, a21, a22}})
{}

std::optional<TransformationMatrix> TransformationMatrix::GetInverse() const
{
  // Compute the determinant
  auto det = Determinant();

  // Compute the inverse if the determinant is not zero
  if (det == complex{0}) return std::nullopt;

  // Return the inverse
  return TransformationMatrix(
      (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) / det,
      -(matrix_[0][1] * matrix_[2][2] - matrix_[0][2] * matrix_[2][1]) / det,
      (matrix_[0][1] * matrix_[1][2] - matrix_[0][2] * matrix_[1][1]) / det,

      -(matrix_[1][0] * matrix_[2][2] - matrix_[1][2] * matrix_[2][0]) / det,
      (matrix_[0][0] * matrix_[2][2] - matrix_[0][2] * matrix_[2][0]) / det,
      -(matrix_[0][0] * matrix_[1][2] - matrix_[0][2] * matrix_[1][0]) / det,

      (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]) / det,
      -(matrix_[0][0] * matrix_[2][1] - matrix_[0][1] * matrix_[2][0]) / det,
      (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]) / det);
}

complex TransformationMatrix::Determinant() const
{
  // Compute the determinant
  return matrix_[0][0] *
             (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) -
         matrix_[0][1] *
             (matrix_[1][0] * matrix_[2][2] - matrix_[1][2] * matrix_[2][0]) +
         matrix_[0][2] *
             (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]);
}

TransformationMatrix& TransformationMatrix::operator*=(
    const TransformationMatrix& other)
{
  // Assigning multiplication result to this
  (*this) = (*this) * other;

  // Returning this
  return *this;
}

TransformationMatrix TransformationMatrix::operator*(
    const TransformationMatrix& other) const
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

const TransformationMatrix::MatrixRow& TransformationMatrix::operator[](
    size_t row) const
{
  return matrix_[row];
}

TransformationMatrix::MatrixRow& TransformationMatrix::operator[](size_t row)
{
  return matrix_[row];
}

TransformationMatrix::MatrixContainer::const_iterator
TransformationMatrix::begin() const
{
  return matrix_.begin();
}

TransformationMatrix::MatrixContainer::const_iterator
TransformationMatrix::end() const
{
  return matrix_.end();
}

Transformation::Transformation(const TransformationMatrix& transformation)
    : transformation_(transformation)
{}

Transformation::Transformation(
    const PointEquation& first_preimage, const PointEquation& second_preimage,
    const PointEquation& third_preimage, const PointEquation& fourth_preimage,
    const PointEquation& first_image, const PointEquation& second_image,
    const PointEquation& third_image, const PointEquation& fourth_image)
{
  // Get equation of all images and preimages
  auto& first_preimage_equation = first_preimage.GetEquation();
  auto& second_preimage_equation = second_preimage.GetEquation();
  auto& third_preimage_equation = third_preimage.GetEquation();
  auto& fourth_preimage_equation = fourth_preimage.GetEquation();

  auto& first_image_equation = first_image.GetEquation();
  auto& second_image_equation = second_image.GetEquation();
  auto& third_image_equation = third_image.GetEquation();
  auto& fourth_image_equation = fourth_image.GetEquation();

  /*
   * We want to find matrix
   *     |h1 h2 h3|
   * H:  |h4 h5 h6|
   *     |h7 h8 h9|
   *
   * For which it is true that H * Preimage = Image
   *
   * For all pairs of Preimage and Image we will write 3 equations
   *
   * We describe the multiplication of a matrix by a vector
   *
   * Assume preimage is (x,y,z) and image is (x',y',z')
   *
   * But we have coordinates with the accuracy of proportionality.
   *
   * So we want to find any matrix H. We will add 3 more variables: first_lamda,
   * second_lamda, third_lamda, so our coordinates for first 3 image are (x' *
   * lamda, y' * lamda, z' * lamda) And for fourth point we will "fix" its
   * coordinates.
   *
   * We will write 3 equations for each pair of preimage and image
   *
   * h1 * x + h2 * y + h3 * z = x' * first_lamda
   * h4 * x + h5 * y + h6 * z = y' * second_lamda
   * h7 * x + h8 * y + h9 * z = z' * third_lamda
   *
   * Move all the summands to the left.
   *
   * h1 * x + h2 * y + h3 * z - x' * first_lamda = 0
   * h4 * x + h5 * y + h6 * z - y' * second_lamda = 0
   * h7 * x + h8 * y + h9 * z - z' * third_lamda = 0
   *
   * For the fourth one we will have these 3 equations
   *
   * h1 * x + h2 * y + h3 * z = x'
   * h4 * x + h5 * y + h6 * z = y'
   * h7 * x + h8 * y + h9 * z = z'
   *
   * So in sum we have 12 variables and 12 equations.
   *
   * Let's put them into matrix with augmentation and solve this system of
   * linear equations.
   */

  SquaredMatrix matrix(
      // Matrix
      {
          // First three rows
          {first_preimage_equation.x, first_preimage_equation.y,
           first_preimage_equation.z, 0, 0, 0, 0, 0, 0, -first_image_equation.x,
           0, 0},
          {0, 0, 0, first_preimage_equation.x, first_preimage_equation.y,
           first_preimage_equation.z, 0, 0, 0, -first_image_equation.y, 0, 0},
          {0, 0, 0, 0, 0, 0, first_preimage_equation.x,
           first_preimage_equation.y, first_preimage_equation.z,
           -first_image_equation.z, 0, 0},

          // Second three rows
          {second_preimage_equation.x, second_preimage_equation.y,
           second_preimage_equation.z, 0, 0, 0, 0, 0, 0, 0,
           -second_image_equation.x, 0},
          {0, 0, 0, second_preimage_equation.x, second_preimage_equation.y,
           second_image_equation.z, 0, 0, 0, 0, -second_image_equation.y, 0},
          {0, 0, 0, 0, 0, 0, second_preimage_equation.x,
           second_preimage_equation.y, second_preimage_equation.z, 0,
           -second_image_equation.z, 0},

          // Third three rows
          {third_preimage_equation.x, third_preimage_equation.y,
           third_preimage_equation.z, 0, 0, 0, 0, 0, 0, 0, 0,
           -third_image_equation.x},
          {0, 0, 0, third_preimage_equation.x, third_preimage_equation.y,
           third_preimage_equation.z, 0, 0, 0, 0, 0, -third_image_equation.y},
          {0, 0, 0, 0, 0, 0, third_preimage_equation.x,
           third_preimage_equation.y, third_preimage_equation.z, 0, 0,
           -third_image_equation.z},

          // Fourth three rows
          {fourth_preimage_equation.x, fourth_preimage_equation.y,
           fourth_preimage_equation.z, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, fourth_preimage_equation.x, fourth_preimage_equation.y,
           fourth_preimage_equation.z, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, fourth_preimage_equation.x,
           fourth_preimage_equation.y, fourth_preimage_equation.z, 0, 0, 0},
      },

      // Augmentation
      {0, 0, 0, 0, 0, 0, 0, 0, 0, fourth_image_equation.x,
       fourth_image_equation.y, fourth_image_equation.z});

  // Solve system of linear equations
  auto solution = matrix.GetSolution();

  // Check if solution exists
  if (!solution)
  {
    throw std::invalid_argument("No solution");
  }

  // Init transformation
  transformation_ = TransformationMatrix(
      solution.value()[0], solution.value()[1], solution.value()[2],
      solution.value()[3], solution.value()[4], solution.value()[5],
      solution.value()[6], solution.value()[7], solution.value()[8]);
}

std::optional<Transformation> Transformation::GetInverse() const
{
  // Return inverse transformation
  return std::optional<Transformation>(transformation_.GetInverse());
}

Transformation& Transformation::operator*=(const Transformation& other)
{
  // Multiply on matrix
  transformation_ *= other.transformation_;

  // Return this
  return *this;
}

Transformation Transformation::operator*(const Transformation& other) const
{
  // Multiply two matrices
  return Transformation(transformation_ * other.transformation_);
}

HomogeneousCoordinate Transformation::operator()(
    const HomogeneousCoordinate& coordinate) const
{
  // Apply transformation and return result
  return (*this) * coordinate;
}

HomogeneousCoordinate& operator*=(HomogeneousCoordinate& coordinate,
                                  const Transformation& transformation)
{
  // Apply transformation
  coordinate = transformation * coordinate;

  // Return coordinate
  return coordinate;
}

HomogeneousCoordinate operator*(const Transformation& transformation,
                                const HomogeneousCoordinate& coordinate)
{
  // Copy coordinate
  auto copy = coordinate;

  // Apply transformation
  for (size_t row = 0; row < std::tuple_size<Transformation::Column>::value;
       ++row)
  {
    // Calculate element
    complex element{0};
    for (size_t column = 0;
         column < std::tuple_size<Transformation::Row>::value; ++column)
    {
      element += coordinate[static_cast<var>(column)] *
                 transformation.transformation_[row][column];
    }

    // Set element
    copy[static_cast<var>(row)] = element;
  }

  // Return copy
  return copy;
}

const complex& HomogeneousCoordinate::operator[](var variable) const
{
  // Return value
  switch (variable)
  {
    case var::kX:
      return x;
    case var::kY:
      return y;
    case var::kZ:
      return z;
    default:
      throw std::invalid_argument("No such variable!");
  }
}

complex& HomogeneousCoordinate::operator[](var variable)
{
  // Return value
  switch (variable)
  {
    case var::kX:
      return x;
    case var::kY:
      return y;
    case var::kZ:
      return z;
    default:
      throw std::invalid_argument("No such variable!");
  }
}