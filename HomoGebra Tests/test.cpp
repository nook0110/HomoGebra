#include "../HomoGebra/Assert.h"
#include "../HomoGebra/Complex.cpp"
#include "../HomoGebra/Complex.h"
#include "../HomoGebra/Coordinate.cpp"  // NOLINT(bugprone-suspicious-include)
#include "../HomoGebra/Coordinate.h"
#include "../HomoGebra/Equation.cpp"
#include "../HomoGebra/Equation.h"
#include "../HomoGebra/Matrix.cpp"
#include "../HomoGebra/Matrix.h"
#include "../HomoGebra/NameGenerator.cpp"
#include "../HomoGebra/NameGenerator.h"
#include "gtest/gtest.h"

using namespace HomoGebra;

namespace HomogebraTest
{
inline constexpr auto kEpsilon = 1e-20L;
namespace HelpFunctions
{
// Checks that two complex number are equal with precision [abs_error]
testing::AssertionResult check_two_complex(const Complex& first,
                                           const Complex& second,
                                           long double abs_error)
{
  if (abs(first.real() - second.real()) < abs_error &&
      abs(first.imag() - second.imag()) < abs_error)
  {
    return testing::AssertionSuccess()
           << "First: " << first.real() << " " << first.imag() << " "
           << "Second: " << second.real() << " " << second.imag()
           << " are near equal!";
  }
  return testing::AssertionFailure()
         << "First: " << first.real() << " " << first.imag() << " "
         << "Second: " << second.real() << " " << second.imag()
         << " are not near equal!";
}

// Checks that two vectors which filled with complex number are equal with
// precision [abs_error]
testing::AssertionResult check_two_vectors(const std::vector<Complex>& first,
                                           const std::vector<Complex>& second,
                                           const long double abs_error)
{
  if (first.size() != second.size())
  {
    return testing::AssertionFailure()
           << "First vector size: " << first.size() << " "
           << "Second vector size: " << second.size() << " are not equal!";
  }

  for (size_t i = 0; i < first.size(); ++i)
  {
    auto result = check_two_complex(first[i], second[i], abs_error);

    if (!result)
    {
      return testing::AssertionFailure() << "Vectors are not near equal! "
                                         << "Index: " << i;
    }
  }

  return testing::AssertionSuccess() << "Vectors are near equal!";
}
}  // namespace HelpFunctions

using namespace HelpFunctions;

namespace Matrix
{
// Checks that two squared matrix are equal with precision [abs_error]
testing::AssertionResult check_two_squared_matrix(
    const ComplexSquaredMatrix& first, const ComplexSquaredMatrix& second,
    long double abs_error)
{
  if (first.GetSize() != second.GetSize())
  {
    return testing::AssertionFailure()
           << "First matrix size: " << first.GetSize() << " "
           << "Second matrix size: " << second.GetSize() << " are not equal!";
  }

  for (size_t row = 0; row < first.GetSize(); ++row)
  {
    for (size_t column = 0; column < first.GetSize(); ++column)
    {
      auto result =
          check_two_complex(first[row][column], second[row][column], abs_error);

      if (!result)
      {
        return testing::AssertionFailure()
               << "Matrices are not near equal! "
               << "Row: " << row << " Column: " << column;
      }
    }
  }

  return testing::AssertionSuccess() << "Matrices are near equal!";
}

// Checks that augmentations of two squared matrices are equal with precision
// [abs_error]
testing::AssertionResult check_two_augmentation(
    const ComplexSquaredMatrix& first, const ComplexSquaredMatrix& second,
    long double abs_error)
{
  if (first.GetSize() != second.GetSize())
  {
    return testing::AssertionFailure()
           << "First matrix size: " << first.GetSize() << " "
           << "Second matrix size: " << second.GetSize() << " are not equal!";
  }

  for (size_t row = 0; row < first.GetSize(); ++row)
  {
    auto result = check_two_complex(first.GetAugmentation()[row],
                                    second.GetAugmentation()[row], abs_error);

    if (!result)
    {
      return testing::AssertionFailure() << "Augmentations are not near equal! "
                                         << "Row: " << row;
    }
  }

  return testing::AssertionSuccess() << "Augmentations are near equal!";
}

class ComplexSquaredMatrixTF : public testing::Test
{
 protected:
  const ComplexSquaredMatrix singular_matrix{
      ComplexSquaredMatrix::Matrix{
          ComplexSquaredMatrix::Row{Complex(1.0, 2.0), Complex(3.0, 4.0),
                                    Complex(5.0, 6.0)},
          ComplexSquaredMatrix::Row{Complex(7.0, 8.0), Complex(9.0, 10.0),
                                    Complex(11.0, 12.0)},
          ComplexSquaredMatrix::Row{Complex(8.0, 10.0), Complex(12.0, 14.0),
                                    Complex(16.0, 18.0)}},
      ComplexSquaredMatrix::Row{Complex(19.0, 20.0), Complex(21.0, 22.0),
                                Complex(23.0, 24.0)}};

  const ComplexSquaredMatrix non_singular_matrix{
      ComplexSquaredMatrix::Matrix{
          ComplexSquaredMatrix::Row{Complex(1.0, 1.2), Complex(2.0, 4.12),
                                    Complex(3.0, 7.636)},
          ComplexSquaredMatrix::Row{Complex(1.0, 2.8), Complex(5.0, 5.521),
                                    Complex(6.0, 8.616)},
          ComplexSquaredMatrix::Row{Complex(1.0, 3.8), Complex(8.0, 6.1234),
                                    Complex(9.0, 9.93)}},
      ComplexSquaredMatrix::Row{Complex(1.0, 0.0), Complex(11.0, 0.0),
                                Complex(12.0, 0.0)}};
};

TEST_F(ComplexSquaredMatrixTF, Inverse)
{
  // Get inverse matrix
  const auto inverse_matrix = singular_matrix.GetInverse();

  // Check that inverse matrix is empty
  ASSERT_FALSE(inverse_matrix.has_value());

  const ComplexSquaredMatrix real_inverse_of_matrix(
      {ComplexSquaredMatrix::Row{Complex(-0.162603872026L, 0.547316949016L),
                                 Complex(1.29642322808L, -0.91383483088),
                                 Complex(-0.887012829208L, 0.302306240654L)},
       ComplexSquaredMatrix::Row{Complex(0.104126199172L, 0.608370065879L),
                                 Complex(-0.83038879224L, -1.40436460852),
                                 Complex(0.577032792198L, 0.8034071115L)},
       ComplexSquaredMatrix::Row{Complex(-0.043135151367L, -0.556184119699L),
                                 Complex(0.343429483128L, 0.988543488361L),
                                 Complex(-0.213740448132L, -0.529986036879L)}},
      ComplexSquaredMatrix::Row{Complex(3.45389768638, -5.87719130279),
                                Complex(-2.10575700912, -5.19875528911),
                                Complex(1.16970378546, 3.95796180972)});

  // Get inverse matrix
  const auto second_inverse_matrix = non_singular_matrix.GetInverse();

  // Check that inverse matrix is not empty
  ASSERT_TRUE(second_inverse_matrix.has_value());

  // Check that inverse matrix is correct
  ASSERT_TRUE(check_two_squared_matrix(
      real_inverse_of_matrix,
      second_inverse_matrix  // NOLINT(bugprone-unchecked-optional-access)
          .value(),
      kEpsilon));

  // Check that augmentation is correct
  ASSERT_TRUE(check_two_augmentation(
      real_inverse_of_matrix,
      second_inverse_matrix  // NOLINT(bugprone-unchecked-optional-access)
          .value(),
      kEpsilon));
}

TEST_F(ComplexSquaredMatrixTF, Solution)
{
  // Get solution
  const auto solution = non_singular_matrix.GetSolution();

  // Check that solution is not empty
  ASSERT_TRUE(solution.has_value());

  // Real solution
  const std::vector<Complex> real_solution = {
      Complex(3.45389768638, -5.87719130279),
      Complex(-2.10575700912, -5.19875528911),
      Complex(1.16970378546, 3.95796180972)};

  // Check that solution is correct
  ASSERT_TRUE(check_two_vectors(
      real_solution,
      solution.value(),  // NOLINT(bugprone-unchecked-optional-access)
      kEpsilon));
}

TEST_F(ComplexSquaredMatrixTF, Determinant)
{
  // Get determinant
  const auto determinant = non_singular_matrix.GetDeterminant();

  // Construct real determinant
  const auto real_determinant =
      Complex(-8.100441999999997478, 11.659567359999980951);

  // Check that determinant is correct
  ASSERT_TRUE(check_two_complex(real_determinant, determinant, kEpsilon));

  // Get determinant
  const auto determinant_with_zero_determinant =
      singular_matrix.GetDeterminant();

  // Check that determinant is 0
  ASSERT_TRUE(check_two_complex(Complex(0.0, 0.0),
                                determinant_with_zero_determinant, kEpsilon));
}
}  // namespace Matrix

namespace Coordinate
{
// Checks that two matrices are equal [each element] with precision
// [abs_error]
testing::AssertionResult check_two_matrix(const TransformationMatrix& first,
                                          const TransformationMatrix& second,
                                          const long double abs_error)
{
  for (size_t row = 0;
       row < std::tuple_size_v<TransformationMatrix::MatrixColumn>; ++row)
  {
    for (size_t column = 0;
         column < std::tuple_size_v<TransformationMatrix::MatrixColumn>;
         ++column)
    {
      if (auto result = check_two_complex(first[row][column],
                                          second[row][column], abs_error);
          !result)
      {
        return testing::AssertionFailure() << "Matrices are not near equal!"
                                           << "\n"
                                           << "Place: "
                                           << "Row: " << row << " "
                                           << "Column: " << column << "\n"
                                           << result.failure_message();
      }
    }
  }
  return testing::AssertionSuccess() << "Matrices are near equal!";
}

class TransformationMatrixTF : public testing::Test
{
 protected:
  const TransformationMatrix matrix{
      Complex(-4.924, -2.768), Complex(0.248, 9.890),   Complex(2.895, 8.700),

      Complex(-5.526, -0.244), Complex(5.526, -3.827),  Complex(-7.857, 1.492),

      Complex(7.554, 2.673),   Complex(-9.136, -7.834), Complex(2.573, 0.384)};

  const TransformationMatrix identity;
};

TEST_F(TransformationMatrixTF, Determinant)
{
  //////
  /// {{-4.924+i*-2.768,
  /// 0.248+i*9.890, 2.895+i*8.700},{-5.526+i*-0.244, 5.526+i*-3.827,
  /// -7.857+i*1.492},{7.554+i*2.673, -9.136+i*-7.834, 2.573+i*0.384}}
  /// determinant is about complex { -292.293300759 , 116.289449988 }
  //////

  // Compute determinant
  const auto det = matrix.Determinant();

  // Check answer
  EXPECT_TRUE(
      check_two_complex(det, Complex{-292.293300759, 116.289449988}, kEpsilon));
}

TEST_F(TransformationMatrixTF, Inverse)
{
  // Find inverse matrix
  const auto inverse_of_identity = identity.GetInverse();

  // Check existing
  ASSERT_TRUE(inverse_of_identity.has_value());

  // Check answer
  EXPECT_TRUE(check_two_matrix(
      identity,
      inverse_of_identity  // NOLINT(bugprone-unchecked-optional-access)
          .value(),
      kEpsilon));

  // Compute inverse
  const auto inverse = matrix.GetInverse();

  // Check existing
  ASSERT_TRUE(inverse.has_value());

  // Construct answer
  const auto correct_inverse =
      TransformationMatrix(Complex(0.1348158592L, 0.2440130339L),
                           Complex(-0.2825926019L, 0.3244764540L),
                           Complex(0.0605789998L, 0.4152590814L),
                           Complex(0.1371624775L, 0.0784552571L),
                           Complex(-0.0667268117L, 0.2556041845L),
                           Complex(0.0932030558L, 0.2532479530L),
                           Complex(0.0801454791L, -0.1722172701L),
                           Complex(0.1548992180L, 0.0222524596L),
                           Complex(0.1832029399L, -0.1264355453L));

  // Check answer
  EXPECT_TRUE(
      check_two_matrix(correct_inverse,
                       inverse  // NOLINT(bugprone-unchecked-optional-access)
                           .value(),
                       kEpsilon));

  // Create a random transformation with determinant 0
  const TransformationMatrix transformation_without_inversion(
      Complex(1, 2), Complex(3, 4), Complex(5, 6), Complex(7, 8),
      Complex(9, 10), Complex(11, 12), Complex(13, 14), Complex(15, 16),
      Complex(17, 18));

  // Compute inverse
  const auto inverse_of_transformation_without_inversion =
      transformation_without_inversion.GetInverse();

  // Check existing
  ASSERT_FALSE(inverse_of_transformation_without_inversion.has_value());
}

TEST_F(TransformationMatrixTF, Multiplication)
{
  // Check some simple multiplications
  EXPECT_TRUE(check_two_matrix(matrix * identity, matrix, kEpsilon));
  EXPECT_TRUE(check_two_matrix(identity * matrix, matrix, kEpsilon));
  EXPECT_TRUE(check_two_matrix(identity * identity, identity, kEpsilon));

  // Compute inverse
  const auto inverse = matrix.GetInverse();

  // Check if inverse matrix exists
  ASSERT_TRUE(inverse.has_value());

  // Checks A*A^-1 = E = A^-1*A
  EXPECT_TRUE(check_two_matrix(
      matrix * inverse  // NOLINT(bugprone-unchecked-optional-access)
                   .value(),
      identity, kEpsilon));
  EXPECT_TRUE(
      check_two_matrix(inverse  // NOLINT(bugprone-unchecked-optional-access)
                               .value() *
                           matrix,
                       identity, kEpsilon));

  // Create matrix^2
  const TransformationMatrix squared_matrix(
      Complex(16.24039400L, 46.00474700L), Complex(107.0809260L, -97.8444100L),
      Complex(-2.76976100L, -104.69109400L),
      Complex(-68.27572600L, 26.56588900L),
      Complex(100.40333900L, -49.08783000L),
      Complex(-72.37185700L, -9.64722100L), Complex(37.18701800L, 21.22690900L),
      Complex(-125.52750400L, 43.37964600L),
      Complex(88.5564830L, 123.3550250L));

  // Check some multiplications
  EXPECT_TRUE(check_two_matrix(matrix * matrix, squared_matrix, kEpsilon));
  EXPECT_TRUE(check_two_matrix(
      squared_matrix * inverse  // NOLINT(bugprone-unchecked-optional-access)
                           .value(),
      matrix, kEpsilon));
  EXPECT_TRUE(
      check_two_matrix(inverse  // NOLINT(bugprone-unchecked-optional-access)
                               .value() *
                           squared_matrix,
                       matrix, kEpsilon));
}

// Checks that two coordinates are near equal
testing::AssertionResult check_two_coordinates(
    const HomogeneousCoordinate& first, const HomogeneousCoordinate& second,
    long double abs_error)
{
  for (Var variable = Var::kX; variable <= Var::kZ;
       variable = static_cast<Var>(static_cast<int>(variable) + 1))
  {
    auto result =
        check_two_complex(first[variable], second[variable], abs_error);
    if (!result)
      return testing::AssertionFailure()
             << "Coordinates are not near equal!"
             << "\n"
             << "Var: " << static_cast<int>(variable) << "\n"
             << result.failure_message();
  }
  return testing::AssertionSuccess() << "Coordinates are near equal!";
}

TEST(Transformation, From_points_constructor)
{
  // Construct ID (images = preimages)
  PointEquation a_id({Complex(1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation b_id({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation c_id({Complex(1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation d_id({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  PointEquation a_image_id({Complex(1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation b_image_id({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation c_image_id({Complex(1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation d_image_id({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  // Construct a transformation from 4 preimages and 4 images
  Transformation id(a_id, b_id, c_id, d_id, a_image_id, b_image_id, c_image_id,
                    d_image_id);

  // Construct random point equation
  PointEquation point({Complex{3, 1}, Complex{1, 2}, Complex{1, 2}});

  // Check that the point is image of itself
  EXPECT_TRUE(
      check_two_coordinates(id(point.equation), point.equation, kEpsilon));

  // Construct Homothety
  PointEquation a_homothety({Complex(1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation b_homothety({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation c_homothety({Complex(1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation d_homothety({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  PointEquation a_image_homothety(
      {Complex(2, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation b_image_homothety(
      {Complex(0, 0), Complex(2, 0), Complex(1, 0)});
  PointEquation c_image_homothety(
      {Complex(2, 0), Complex(2, 0), Complex(1, 0)});
  PointEquation d_image_homothety(
      {Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  // Construct a transformation from 4 preimages and 4 images
  Transformation homothety(a_homothety, b_homothety, c_homothety, d_homothety,
                           a_image_homothety, b_image_homothety,
                           c_image_homothety, d_image_homothety);

  // Construct random point equation
  PointEquation point_homothety({Complex{3, 1}, Complex{1, 2}, Complex{1, 2}});

  // Construct answer
  PointEquation point_homothety_image(
      {Complex{6, 2}, Complex{2, 4}, Complex{1, 2}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(homothety(point_homothety.equation),
                                    point_homothety_image.equation, kEpsilon));

  // Construct a rotation
  PointEquation A_rotation({Complex(1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation B_rotation({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation C_rotation({Complex(1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation D_rotation({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  PointEquation A_image_rotation({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation B_image_rotation(
      {Complex(-1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation C_image_rotation(
      {Complex(-1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation D_image_rotation({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  // Construct a transformation from 4 preimages and 4 images
  Transformation rotation(A_rotation, B_rotation, C_rotation, D_rotation,
                          A_image_rotation, B_image_rotation, C_image_rotation,
                          D_image_rotation);

  // Construct random point equation
  PointEquation point_rotation({Complex{3, 0}, Complex{1, 0}, Complex{1, 0}});

  // Construct answer
  PointEquation point_rotation_image(
      {Complex{-1, 0}, Complex{3, 0}, Complex{1, 0}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(rotation(point_rotation.equation),
                                    point_rotation_image.equation, kEpsilon));

  // Construct a translation
  PointEquation A_translation({Complex(1, 0), Complex(0, 0), Complex(1, 0)});
  PointEquation B_translation({Complex(0, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation C_translation({Complex(1, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation D_translation({Complex(0, 0), Complex(0, 0), Complex(1, 0)});

  PointEquation A_image_translation(
      {Complex(2, 0), Complex(1, 0), Complex(1, 0)});
  PointEquation B_image_translation(
      {Complex(1, 0), Complex(2, 0), Complex(1, 0)});
  PointEquation C_image_translation(
      {Complex(2, 0), Complex(2, 0), Complex(1, 0)});
  PointEquation D_image_translation(
      {Complex(1, 0), Complex(1, 0), Complex(1, 0)});

  // Construct a transformation from 4 preimages and 4 images
  Transformation translation(A_translation, B_translation, C_translation,
                             D_translation, A_image_translation,
                             B_image_translation, C_image_translation,
                             D_image_translation);

  // Construct random point equation
  PointEquation point_translation(
      {Complex{3, 0}, Complex{1, 0}, Complex{1, 0}});

  // Construct answer
  PointEquation point_translation_image(
      {Complex{4, 0}, Complex{2, 0}, Complex{1, 0}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(translation(point_translation.equation),
                                    point_translation_image.equation,
                                    kEpsilon));

  // Construct a composition
  Transformation composition = translation * rotation * homothety;

  // Construct random point equation
  PointEquation point_composition(
      {Complex{3, 0}, Complex{1, 0}, Complex{1, 0}});

  // Construct answer
  PointEquation point_composition_image(
      {Complex{-1, 0}, Complex{7, 0}, Complex{1, 0}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(composition(point_composition.equation),
                                    point_composition_image.equation,
                                    kEpsilon));

  // Construct a composition
  Transformation composition2 = homothety * rotation * translation;

  // Construct random point equation
  PointEquation point_composition2(
      {Complex{3, 0}, Complex{1, 0}, Complex{1, 0}});

  // Construct answer
  PointEquation point_composition2_image(
      {Complex{-4, 0}, Complex{8, 0}, Complex{1, 0}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(composition2(point_composition2.equation),
                                    point_composition2_image.equation,
                                    kEpsilon));

  // Construct a composition
  Transformation composition3 = translation * homothety * rotation;

  // Construct random point equation
  PointEquation point_composition3(
      {Complex{3, 0}, Complex{1, 0}, Complex{1, 0}});

  // Construct answer
  PointEquation point_composition3_image(
      {Complex{-1, 0}, Complex{7, 0}, Complex{1, 0}});

  // Check transformation
  EXPECT_TRUE(check_two_coordinates(composition3(point_composition3.equation),
                                    point_composition3_image.equation,
                                    kEpsilon));
}

TEST(Transformation, Multiplication)
{
  // Create random matrix
  const Transformation transformation(TransformationMatrix(
      Complex(-4.924, -2.768), Complex(0.248, 9.890), Complex(2.895, 8.700),

      Complex(-5.526, -0.244), Complex(5.526, -3.827), Complex(-7.857, 1.492),

      Complex(7.554, 2.673), Complex(-9.136, -7.834), Complex(2.573, 0.384)));

  // Create random point
  const HomogeneousCoordinate point{
      Complex(-2.728, 2.730), Complex(8.852, -2.598), Complex(-2.883, 6.312)};

  // Check Id transform
  EXPECT_TRUE(check_two_coordinates(Transformation() * point, point, kEpsilon));

  // Create real answer to transformation * point
  const HomogeneousCoordinate answer{Complex(-14.38185700, 74.2017000),
                                     Complex(67.94888100, -116.54832000),
                                     Complex(-138.97097300, -17.14706000)};

  // Check answer
  EXPECT_TRUE(check_two_coordinates(transformation * point, answer, kEpsilon));

  // Create zero point
  const HomogeneousCoordinate zero_coord{Complex(0), Complex(0), Complex(0)};

  // Check transform of zero point
  EXPECT_TRUE(
      check_two_coordinates(transformation * zero_coord, zero_coord, kEpsilon));

  // Create zero transformation
  const Transformation zero_trans(
      TransformationMatrix(Complex(0), Complex(0), Complex(0),

                           Complex(0), Complex(0), Complex(0),

                           Complex(0), Complex(0), Complex(0)));

  // Check zero transformation
  EXPECT_TRUE(check_two_coordinates(zero_trans * point, zero_coord, kEpsilon));
}
}  // namespace Coordinate

namespace NameGen
{
TEST(Subname, ParseSubname)
{
  // Create a subname without digits
  const std::string subname_without_digits = "W/O digits";

  // Parse a subname
  const auto parsed_subname_wo_digits =
      NameGenerator::ParseSubname(subname_without_digits);

  // Check
  EXPECT_EQ(parsed_subname_wo_digits.subname, subname_without_digits);
  ASSERT_TRUE(!parsed_subname_wo_digits.number.has_value());

  // Create a subname with only digits
  constexpr size_t number = 239932239;
  const std::string subname_only_digits = std::to_string(number);

  // Parse a subname
  const auto parsed_subname_only_digits =
      NameGenerator::ParseSubname(subname_only_digits);

  // Check
  EXPECT_EQ(parsed_subname_only_digits.subname, std::string{});
  ASSERT_TRUE(parsed_subname_only_digits.number.has_value());
  EXPECT_EQ(parsed_subname_only_digits.number.value(), number);

  // Create subname with some text and number
  const std::string silly_text = "Some silly text";
  const std::string subname = silly_text + std::to_string(number);

  // Parse
  const auto parsed_subname = NameGenerator::ParseSubname(subname);

  // Check
  EXPECT_EQ(parsed_subname.subname, silly_text);
  ASSERT_TRUE(parsed_subname.number.has_value());
  EXPECT_EQ(parsed_subname.number.value(), number);

  // Create subname with some text and number, again text and again number
  const std::string multi_number_subname = subname + subname;

  // Parse
  const auto parsed_multi_subname =
      NameGenerator::ParseSubname(multi_number_subname);

  // Check
  EXPECT_EQ(parsed_multi_subname.subname, subname + silly_text);
  ASSERT_TRUE(parsed_multi_subname.number.has_value());
  EXPECT_EQ(parsed_multi_subname.number.value(), number);
}

TEST(Name, ParseName)
{
  // Create a subname without digits
  const std::string name_without_underscore = "W/O underscore";

  // Parse a subname
  const auto parsed_name_without_underscore =
      NameGenerator::ParseName(name_without_underscore);

  // Check
  EXPECT_EQ(parsed_name_without_underscore.name, name_without_underscore);
  EXPECT_EQ(parsed_name_without_underscore.parsed_subname, ParsedSubname());

  // Create a subname without digits but with underscore
  constexpr auto kUnderscore = '_';
  const std::string name_without_digits_with_underscore =
      name_without_underscore + kUnderscore;

  // Parse a subname
  const auto parsed_name_wo_digits_with_underscore =
      NameGenerator::ParseName(name_without_digits_with_underscore);

  // Check
  EXPECT_EQ(parsed_name_wo_digits_with_underscore.name,
            name_without_underscore);
  EXPECT_EQ(parsed_name_wo_digits_with_underscore.parsed_subname,
            ParsedSubname());

  constexpr size_t number = 239;
  const std::string silly_text = "Some silly text";

  // Test 1
  // Init
  const std::string first_name =
      silly_text + kUnderscore + std::to_string(number);

  // Parse
  const auto first_parsed_name = NameGenerator::ParseName(first_name);

  EXPECT_EQ(first_parsed_name.name, silly_text);
  EXPECT_EQ(first_parsed_name.parsed_subname, ParsedSubname({"", number}));

  // Test 2
  // Init
  const std::string second_name = silly_text + kUnderscore + silly_text;

  // Parse
  const auto second_parsed_name = NameGenerator::ParseName(second_name);

  // Check
  EXPECT_EQ(second_parsed_name.name, silly_text);
  EXPECT_EQ(second_parsed_name.parsed_subname, ParsedSubname({silly_text, {}}));

  // Test 3
  // Init
  const std::string third_name =
      silly_text + kUnderscore + silly_text + std::to_string(number);

  // Parse
  const auto third_parsed_name = NameGenerator::ParseName(third_name);

  // Check
  EXPECT_EQ(third_parsed_name.name, silly_text);
  EXPECT_EQ(third_parsed_name.parsed_subname,
            ParsedSubname({silly_text, number}));
}

TEST(Name, GenName)
{
  // Create a name gen
  NameGenerator name_generator;

  // Create a name
  const std::string name = "name";

  // Create a subname
  const std::string subname = "subname";

  // Create a number
  constexpr size_t number = 239;

  // Create a name with subname
  const std::string name_with_subname = name + "_" + subname;

  // Create a name with subname and number
  const std::string name_with_subname_and_number =
      name_with_subname + std::to_string(number);

  // Check
  EXPECT_EQ(name_generator.GenerateName(name), NameGenerator::ParseName(name));
  EXPECT_EQ(name_generator.GenerateName(name_with_subname),
            NameGenerator::ParseName(name_with_subname));
  EXPECT_EQ(name_generator.GenerateName(name_with_subname_and_number),
            NameGenerator::ParseName(name_with_subname_and_number));

  // Save used name
  name_generator.AddName(name_with_subname_and_number);

  /*
   * Saved names:
   * | "name_subname239"
   */

  // Check
  EXPECT_EQ(name_generator.GenerateName(name_with_subname_and_number),
            NameGenerator::ParseName(name_with_subname));

  // Save used name
  name_generator.AddName(name_with_subname);

  /*
   * Saved names:
   * | "name_subname239"
   * | "name_subname"
   */

  // Parse name
  auto parsed_name = NameGenerator::ParseName(name_with_subname);

  auto adjusted_name = parsed_name;
  adjusted_name.parsed_subname.number = 0;

  // Check
  EXPECT_EQ(name_generator.GenerateName(name_with_subname), adjusted_name);

  // Delete name
  name_generator.DeleteName(name_with_subname);
  /*
   * Saved names:
   * | "name_subname239"
   */

  EXPECT_EQ(name_generator.GenerateName(name_with_subname),
            NameGenerator::ParseName(name_with_subname));
}

TEST(Name, EmptyNameGen)
{
  NameGenerator name_generator;

  EXPECT_EQ(name_generator.GenerateName(), NameGenerator::ParseName("A"));

  // Save name
  name_generator.AddName(NameGenerator::ParseName("A"));

  /*
   * Saved names:
   * | "A"
   */

  EXPECT_EQ(name_generator.GenerateName(), NameGenerator::ParseName("B"));

  constexpr std::string_view kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (const auto character : kAlphabet)
  {
    name_generator.AddName(NameGenerator::ParseName(std::string{character}));
  }

  /*
   * Saved names:
   * | "A"
   * | "B"
   * | ...
   * | "Z"
   */

  // Check
  EXPECT_EQ(name_generator.GenerateName(), NameGenerator::ParseName("A_0"));

  constexpr char kDelimiter = NameGenerator::kDelimiter;
  constexpr char kTestingCharacter = 'K';
  for (const auto character : kAlphabet)
  {
    if (character != kTestingCharacter)
      name_generator.AddName(NameGenerator::ParseName(
          std::string{character} + kDelimiter + std::to_string(0)));
  }

  EXPECT_EQ(name_generator.GenerateName(),
            NameGenerator::ParseName(std::string{kTestingCharacter} +
                                     kDelimiter + std::to_string(0)));
}
}  // namespace NameGen

/*namespace Functions
{
TEST(SolveQuadraticEquation, NoSolution)
{
  constexpr Complex a = 0;
  constexpr Complex b = 0;
  constexpr Complex c = 0;

  const auto answer = SolveQuadraticEquation(a, b, c);

  const std::array<std::optional<Complex>, 2> correct_answer;

  EXPECT_EQ(answer, correct_answer);
}

TEST(SolveQuadraticEquation, LinearEquation)
{
  constexpr Complex a = 0;
  constexpr Complex b = Complex{1, 2};
  constexpr Complex c = Complex{3, 4};

  const auto answer = SolveQuadraticEquation(a, b, c);

  const std::array<std::optional<Complex>, 2> correct_answer = {
      -Complex{3, 4} / Complex{1, 2}, std::nullopt};

  EXPECT_EQ(answer, correct_answer);
}

TEST(SolveQuadraticEquation, QuadraticEquation)
{
  constexpr auto a = Complex{1, 2};
  constexpr auto b = Complex{3, 4};
  constexpr auto c = Complex{5, 6};

  const auto answer = SolveQuadraticEquation(a, b, c);

  const std::array<Complex, 2> correct_answer = {
      Complex{-1.22014865711964, -1.29814408512921},
      Complex{-0.97985134288036, 1.69814408512921}};

  ASSERT_TRUE(answer[0].has_value());
  ASSERT_TRUE(answer[1].has_value());

  EXPECT_TRUE(
      check_two_complex(answer[0].value(), correct_answer[0], kEpsilon));
  EXPECT_TRUE(
      check_two_complex(answer[1].value(), correct_answer[1], kEpsilon));
}
}  // namespace Functions*/
}  // namespace HomogebraTest