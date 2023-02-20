#include "pch.h"
#include "gtest/gtest.h"

#include "../HomoGebra/Matrix.h"
#include "../HomoGebra/Matrix.cpp"
#include "../HomoGebra/Coordinate.h"
#include "../HomoGebra/Coordinate.cpp"
#include "../HomoGebra/Equation.h"
#include "../HomoGebra/Equation.cpp"
#include "../HomoGebra/GeometricObjectImplementation.h"
#include "../HomoGebra/GeometricObjectImplementation.cpp"


constexpr long double epsilon = 1e-10L;

namespace HomogebraTest
{

  // Checks that two complex number are equal with precision [abs_error]
  testing::AssertionResult check_two_complex(const complex& first, const complex& second, long double abs_error)
  {
    if (abs(first.real() - second.real()) < abs_error
        && abs(first.imag() - second.imag()) < abs_error)
    {
      return testing::AssertionSuccess() << "First: " << first.real() << " " << first.imag() << " "
        << "Second: " << second.real() << " " << second.imag() << " are near equal!";
    }
    return testing::AssertionFailure() << "First: " << first.real() << " " << first.imag() << " "
      << "Second: " << second.real() << " " << second.imag() << " are not near equal!";
  }

  // Checks that two vectors which filled with complex number are equal with precision [abs_error]
  testing::AssertionResult check_two_vectors(const std::vector<complex>& first, const std::vector<complex>& second, long double abs_error)
  {
    if (first.size() != second.size())
    {
      return testing::AssertionFailure() << "First vector size: " << first.size() << " "
        << "Second vector size: " << second.size() << " are not equal!";
    }

    for (size_t i = 0; i < first.size(); ++i)
    {
      auto result = check_two_complex(first[i], second[i], abs_error);

      if (!result)
      {
        return testing::AssertionFailure() << "Vectors are not near equal! " << "Index: " << i;
      }
    }

    return testing::AssertionSuccess() << "Vectors are near equal!";
  }

  namespace Matrix
  {
    // Checks that two squared matrix are equal with precision [abs_error]
    testing::AssertionResult check_two_squared_matrix(const SquaredMatrix& first, const SquaredMatrix& second, long double abs_error)
    {
      if (first.GetSize() != second.GetSize())
      {
        return testing::AssertionFailure() << "First matrix size: " << first.GetSize() << " "
          << "Second matrix size: " << second.GetSize() << " are not equal!";
      }

      for (size_t row = 0; row < first.GetSize(); ++row)
      {
        for (size_t column = 0; column < first.GetSize(); ++column)
        {
          auto result = check_two_complex(first[row][column], second[row][column], abs_error);

          if (!result)
          {
            return testing::AssertionFailure() << "Matrices are not near equal! " << "Row: " << row << " Column: " << column;
          }
        }
      }

      return testing::AssertionSuccess() << "Matrices are near equal!";
    }

    // Checks that augmentations of two squared matrices are equal with precision [abs_error]
    testing::AssertionResult check_two_augmentation(const SquaredMatrix& first, const SquaredMatrix& second, long double abs_error)
    {
      if (first.GetSize() != second.GetSize())
      {
        return testing::AssertionFailure() << "First matrix size: " << first.GetSize() << " "
          << "Second matrix size: " << second.GetSize() << " are not equal!";
      }

      for (size_t row = 0; row < first.GetSize(); ++row)
      {
        auto result = check_two_complex(first.GetAugmentation()[row], second.GetAugmentation()[row], abs_error);

        if (!result)
        {
          return testing::AssertionFailure() << "Augmentations are not near equal! " << "Row: " << row;
        }
      }

      return testing::AssertionSuccess() << "Augmentations are near equal!";
    }
    TEST(SquaredMatrix, Inverse)
    {
      // Generate random matrix 3 * 3 with determinant 0
      const SquaredMatrix matrix(
        SquaredMatrix::Matrix {
          SquaredMatrix::Row{ complex(1.0, 2.0), complex(3.0, 4.0), complex(5.0, 6.0) },
          SquaredMatrix::Row{ complex(7.0, 8.0), complex(9.0, 10.0), complex(11.0, 12.0) },
          SquaredMatrix::Row{ complex(8.0, 10.0), complex(12.0, 14.0), complex(16.0, 18.0) }
        },
        SquaredMatrix::Row { complex(19.0, 20.0), complex(21.0, 22.0), complex(23.0, 24.0) }
      );

      // Get inverse matrix
      const auto inverse_matrix = matrix.GetInverse();

      // Check that inverse matrix is empty
      ASSERT_FALSE(inverse_matrix.has_value());

      // Generate another random matrix 3 * 3 with determinant 1


      const SquaredMatrix second_matrix(
        {
          SquaredMatrix::Row{ complex(1.0, 1.2), complex(2.0, 4.12), complex(3.0, 7.636) },
          SquaredMatrix::Row{ complex(1.0, 2.8), complex(5.0, 5.521), complex(6.0, 8.616) },
          SquaredMatrix::Row{ complex(1.0, 3.8), complex(8.0, 6.1234), complex(9.0, 9.93) }
        },
        SquaredMatrix::Row { complex(1.0, 0.0), complex(11.0, 0.0), complex(12.0, 0.0) }
      );
      // {{1+1.2*i, 2+4.12*i, 3+7.636*i}, {1+2.8*i, 5+5.521*i, 6+8.616*i}, {1+3.8*i, 8+6.1234*i, 9+9.93*i}}, {{1, 11, 12}}


      const SquaredMatrix real_inverse_of_matrix(
        {
          SquaredMatrix::Row{ complex(-0.162603872026L, 0.547316949016L), complex(1.29642322808L, -0.91383483088), complex(-0.887012829208L, 0.302306240654L) },
          SquaredMatrix::Row{ complex(0.104126199172L, 0.608370065879L), complex(-0.83038879224L, -1.40436460852), complex(0.577032792198L, 0.8034071115L) },
          SquaredMatrix::Row{ complex(-0.043135151367L, -0.556184119699L), complex(0.343429483128L, 0.988543488361L), complex(-0.213740448132L, -0.529986036879L) }
        },
        SquaredMatrix::Row { complex(3.45389768638, -5.87719130279), complex(-2.10575700912,  -5.19875528911), complex(1.16970378546, 3.95796180972) }
      );
      // {{-0.162603872026+0.547316949016*i, 1.29642322808-0.91383483088*i, -0.887012829208+0.302306240654*i}, {0.104126199172+0.608370065879*i, -0.83038879224-1.40436460852*i, 0.577032792198+0.8034071115*i}, {-0.043135151367-0.556184119699*i, 0.343429483128+0.988543488361*i, -0.213740448132-0.529986036879*i}}, {{3.45389768638-5.87719130279*i, -2.10575700912-5.19875528911*i, 1.16970378546+3.95796180972*i}}

      // Get inverse matrix
      const auto second_inverse_matrix = second_matrix.GetInverse();

      // Check that inverse matrix is not empty
      ASSERT_TRUE(second_inverse_matrix.has_value());

      // Check that inverse matrix is correct
      ASSERT_TRUE(check_two_squared_matrix(real_inverse_of_matrix, second_inverse_matrix.value(), epsilon));

      // Check that augmentation is correct
      ASSERT_TRUE(check_two_augmentation(real_inverse_of_matrix, second_inverse_matrix.value(), epsilon));
    }

    TEST(SquaredMatrix, Solution)
    {
      // Create a random matrix 3 * 3 with determinant 1
      const SquaredMatrix matrix(
        {
          SquaredMatrix::Row{ complex(1.0, 1.2), complex(2.0, 4.12), complex(3.0, 7.636) },
          SquaredMatrix::Row{ complex(1.0, 2.8), complex(5.0, 5.521), complex(6.0, 8.616) },
          SquaredMatrix::Row{ complex(1.0, 3.8), complex(8.0, 6.1234), complex(9.0, 9.93) }
        },
        SquaredMatrix::Row { complex(1.0, 0.0), complex(11.0, 0.0), complex(12.0, 0.0) }
      );

      // {{1.0 + 1.2*i, 2.0 + 4.12*i, 3.0 + 7.636*i}, {1.0 + 2.8*i, 5.0 + 5.521*i, 6.0 + 8.616*i}, {1.0 + 3.8*i, 8.0 + 6.1234*i, 9.0 + 9.93*i}}, {{1.0, 11.0, 12.0}}

      // Get solution
      const auto solution = matrix.GetSolution();

      // Check that solution is not empty
      ASSERT_TRUE(solution.has_value());

      // Real solution

      // { { 3.45389768638 - 5.87719130279 i }, { -2.10575700912 - 5.19875528911 i }, { 1.16970378546 + 3.95796180972 i } }
      const std::vector<complex> real_solution = { complex(3.45389768638, -5.87719130279), complex(-2.10575700912, -5.19875528911), complex(1.16970378546, 3.95796180972) };

      // Check that solution is correct
      ASSERT_TRUE(check_two_vectors(real_solution, solution.value(), epsilon));
    }
  }

  namespace Coordinate
  {
    // Checks that two matrices are equal [each element] with precision [abs_error]
    testing::AssertionResult check_two_matrix(const TransformationMatrix& first, const TransformationMatrix& second, long double abs_error)
    {
      for (int row = 0; row < std::tuple_size<TransformationMatrix::MatrixColumn>::value; ++row)
      {
        for (int column = 0; column < std::tuple_size<TransformationMatrix::MatrixColumn>::value; ++column)
        {
          auto result = check_two_complex(first[row][column], second[row][column], abs_error);
          if (!result)
          {
            return testing::AssertionFailure() << "Matrices are not near equal!" << "\n"
              << "Place: " << "Row: " << row << " " << "Column: " << column << "\n"
              << result.failure_message();
          }
        }
      }
      return testing::AssertionSuccess() << "Matrices are near equal!";
    }

    TEST(TransformationMatrix, Determinant)
    {
      // Create an identity matrix
      const TransformationMatrix identity;

      // Create a random matrix
      const TransformationMatrix matrix(
        complex(-4.924, -2.768),
        complex(0.248, 9.890),
        complex(2.895, 8.700),

        complex(-5.526, -0.244),
        complex(5.526, -3.827),
        complex(-7.857, 1.492),

        complex(7.554, 2.673),
        complex(-9.136, -7.834),
        complex(2.573, 0.384)
      );


      //////
      /// {{-4.924+i*-2.768, 0.248+i*9.890, 2.895+i*8.700},{-5.526+i*-0.244, 5.526+i*-3.827, -7.857+i*1.492},{7.554+i*2.673, -9.136+i*-7.834, 2.573+i*0.384}}
      /// determinant is about complex { -292.293300759 , 116.289449988 }
      //////

      // Compute determinant
      const auto det = matrix.Determinant();

      // Check answer
      EXPECT_TRUE(check_two_complex(det, complex { -292.293300759 , 116.289449988 }, epsilon));
    }

    TEST(TransformationMatrix, Inverse)
    {
      // Create an identity matrix
      const TransformationMatrix identity;

      // Find inverse matrix
      const auto inverse_of_identity = identity.GetInverse();

      // Check existing
      ASSERT_TRUE(inverse_of_identity.has_value());

      // Check answer
      EXPECT_TRUE(check_two_matrix(identity, inverse_of_identity.value(), epsilon));

      // Create a random matrix
      const TransformationMatrix matrix(
        complex(-4.924, -2.768),
        complex(0.248, 9.890),
        complex(2.895, 8.700),

        complex(-5.526, -0.244),
        complex(5.526, -3.827),
        complex(-7.857, 1.492),

        complex(7.554, 2.673),
        complex(-9.136, -7.834),
        complex(2.573, 0.384)
      );

      // Compute inverse
      const auto inverse = matrix.GetInverse();

      // Check existing
      ASSERT_TRUE(inverse.has_value());

      // Construct answer
      const auto correct_inverse = TransformationMatrix(
        complex(0.1348158592L, 0.2440130339L),
        complex(-0.2825926019L, 0.3244764540L),
        complex(0.0605789998L, 0.4152590814L),
        complex(0.1371624775L, 0.0784552571L),
        complex(-0.0667268117L, 0.2556041845L),
        complex(0.0932030558L, 0.2532479530L),
        complex(0.0801454791L, -0.1722172701L),
        complex(0.1548992180L, 0.0222524596L),
        complex(0.1832029399L, -0.1264355453L)
      );

      // Check answer
      EXPECT_TRUE(check_two_matrix(correct_inverse, inverse.value(), epsilon));

      // Create a random transformation with determinant 0
      const TransformationMatrix transformation_without_inversion(
        complex(1, 2), complex(3, 4), complex(5, 6),
        complex(7, 8), complex(9, 10), complex(11, 12),
        complex(13, 14), complex(15, 16), complex(17, 18)
      );

      // Compute inverse
      const auto inverse_of_transformation_without_inversion = transformation_without_inversion.GetInverse();

      // Check existing
      ASSERT_FALSE(inverse_of_transformation_without_inversion.has_value());
    }

    TEST(TransformationMatrix, Multiplication)
    {
      // Create an identity matrix
      const TransformationMatrix identity;

      // Create a random matrix
      const TransformationMatrix matrix(
        complex(-4.924, -2.768),
        complex(0.248, 9.890),
        complex(2.895, 8.700),

        complex(-5.526, -0.244),
        complex(5.526, -3.827),
        complex(-7.857, 1.492),

        complex(7.554, 2.673),
        complex(-9.136, -7.834),
        complex(2.573, 0.384)
      );

      // Check some simple multiplications
      EXPECT_TRUE(check_two_matrix(matrix * identity, matrix, epsilon));
      EXPECT_TRUE(check_two_matrix(identity * matrix, matrix, epsilon));
      EXPECT_TRUE(check_two_matrix(identity * identity, identity, epsilon));

      // Compute inverse
      const auto inverse = matrix.GetInverse();

      // Checks A*A^-1 = E = A^-1*A
      EXPECT_TRUE(check_two_matrix(matrix * inverse.value(), identity, epsilon));
      EXPECT_TRUE(check_two_matrix(inverse.value() * matrix, identity, epsilon));

      // Create matrix^2
      const TransformationMatrix squared_matrix(
        complex(16.24039400L, 46.00474700L),
        complex(107.0809260L, -97.8444100L),
        complex(-2.76976100L, -104.69109400L),
        complex(-68.27572600L, 26.56588900L),
        complex(100.40333900L, -49.08783000L),
        complex(-72.37185700L, -9.64722100L),
        complex(37.18701800L, 21.22690900L),
        complex(-125.52750400L, 43.37964600L),
        complex(88.5564830L, 123.3550250L)
      );

      // Check some multiplications
      EXPECT_TRUE(check_two_matrix(matrix * matrix, squared_matrix, epsilon));
      EXPECT_TRUE(check_two_matrix(squared_matrix * inverse.value(), matrix, epsilon));
      EXPECT_TRUE(check_two_matrix(inverse.value() * squared_matrix, matrix, epsilon));
    }

    // Checks that two coordinates are near equal
    testing::AssertionResult check_two_coordinates(const HomogeneousCoordinate& first, const HomogeneousCoordinate& second, long double abs_error)
    {
      for (var variable = var::kX; variable <= var::kZ; variable = static_cast<var>(static_cast<int>(variable) + 1))
      {
        auto result = check_two_complex(first[variable], second[variable], abs_error);
        if (!result)
          return testing::AssertionFailure() << "Coordinates are not near equal!" << "\n"
          << "Var: " << static_cast<int>(variable) << "\n" << result.failure_message();
      }
      return testing::AssertionSuccess() << "Coordinates are near equal!";
    }

    TEST(Transformation, From_points_constructor)
    {
      // Construct ID (images = preimages)
      PointEquation A_id({ complex(1, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_id({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation C_id({ complex(1, 0), complex(1, 0), complex(1, 0)});
      PointEquation D_id({ complex(0, 0), complex(0, 0), complex(1, 0) });

      PointEquation A_image_id({ complex(1, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_image_id({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation C_image_id({ complex(1, 0), complex(1, 0), complex(1, 0) });
      PointEquation D_image_id({ complex(0, 0), complex(0, 0), complex(1, 0) });

      // Construct a transformation from 4 preimages and 4 images
      Transformation id(A_id, B_id, C_id, D_id,
                     A_image_id, B_image_id, C_image_id, D_image_id);

      // Construct random point equation
      PointEquation point({ complex{3,1}, complex{1, 2}, complex{1, 2} });

      // Check that the point is image of itself
      EXPECT_TRUE(check_two_coordinates(id(point.equation), point.equation, epsilon));

      // Construct Homothety
      PointEquation A_homothety({ complex(1, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_homothety({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation C_homothety({ complex(1, 0), complex(1, 0), complex(1, 0) });
      PointEquation D_homothety({ complex(0, 0), complex(0, 0), complex(1, 0) });

      PointEquation A_image_homothety({ complex(2, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_image_homothety({ complex(0, 0), complex(2, 0), complex(1, 0) });
      PointEquation C_image_homothety({ complex(2, 0), complex(2, 0), complex(1, 0) });
      PointEquation D_image_homothety({ complex(0, 0), complex(0, 0), complex(1, 0) });

      // Construct a transformation from 4 preimages and 4 images
      Transformation homothety(A_homothety, B_homothety, C_homothety, D_homothety,
                                      A_image_homothety, B_image_homothety, C_image_homothety, D_image_homothety);

      // Construct random point equation
      PointEquation point_homothety({ complex{3,1}, complex{1, 2}, complex{1, 2} });

      // Construct answer
      PointEquation point_homothety_image({ complex{6,2}, complex{2, 4}, complex{1, 2} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(homothety(point_homothety.equation), point_homothety_image.equation, epsilon));

      // Construct a rotation
      PointEquation A_rotation({ complex(1, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_rotation({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation C_rotation({ complex(1, 0), complex(1, 0), complex(1, 0) });
      PointEquation D_rotation({ complex(0, 0), complex(0, 0), complex(1, 0) });

      PointEquation A_image_rotation({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation B_image_rotation({ complex(-1, 0), complex(0, 0), complex(1, 0) });
      PointEquation C_image_rotation({ complex(-1, 0), complex(1, 0), complex(1, 0) });
      PointEquation D_image_rotation({ complex(0, 0), complex(0, 0), complex(1, 0) });

      // Construct a transformation from 4 preimages and 4 images
      Transformation rotation(A_rotation, B_rotation, C_rotation, D_rotation,
                                     A_image_rotation, B_image_rotation, C_image_rotation, D_image_rotation);

      // Construct random point equation
      PointEquation point_rotation({ complex{3,0}, complex{1, 0}, complex{1, 0} });

      // Construct answer
      PointEquation point_rotation_image({ complex{-1,0}, complex{3, 0}, complex{1, 0} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(rotation(point_rotation.equation), point_rotation_image.equation, epsilon));

      // Construct a translation
      PointEquation A_translation({ complex(1, 0), complex(0, 0), complex(1, 0) });
      PointEquation B_translation({ complex(0, 0), complex(1, 0), complex(1, 0) });
      PointEquation C_translation({ complex(1, 0), complex(1, 0), complex(1, 0) });
      PointEquation D_translation({ complex(0, 0), complex(0, 0), complex(1, 0) });

      PointEquation A_image_translation({ complex(2, 0), complex(1, 0), complex(1, 0) });
      PointEquation B_image_translation({ complex(1, 0), complex(2, 0), complex(1, 0) });
      PointEquation C_image_translation({ complex(2, 0), complex(2, 0), complex(1, 0) });
      PointEquation D_image_translation({ complex(1, 0), complex(1, 0), complex(1, 0) });

      // Construct a transformation from 4 preimages and 4 images
      Transformation translation(A_translation, B_translation, C_translation, D_translation,
                                                                        A_image_translation, B_image_translation, C_image_translation, D_image_translation);

      // Construct random point equation
      PointEquation point_translation({ complex{3,0}, complex{1, 0}, complex{1, 0} });

      // Construct answer
      PointEquation point_translation_image({ complex{4,0}, complex{2, 0}, complex{1, 0} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(translation(point_translation.equation), point_translation_image.equation, epsilon));
    
      // Construct a composition
      Transformation composition = translation * rotation * homothety;

      // Construct random point equation
      PointEquation point_composition({ complex{3,0}, complex{1, 0}, complex{1, 0} });

      // Construct answer
      PointEquation point_composition_image({ complex{-1,0}, complex{7, 0}, complex{1, 0} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(composition(point_composition.equation), point_composition_image.equation, epsilon));

      // Construct a composition
      Transformation composition2 = homothety * rotation * translation;

      // Construct random point equation
      PointEquation point_composition2({ complex{3,0}, complex{1, 0}, complex{1, 0} });

      // Construct answer
      PointEquation point_composition2_image({ complex{-4,0}, complex{8, 0}, complex{1, 0} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(composition2(point_composition2.equation), point_composition2_image.equation, epsilon));

      // Construct a composition
      Transformation composition3 = translation * homothety * rotation;

      // Construct random point equation
      PointEquation point_composition3({ complex{3,0}, complex{1, 0}, complex{1, 0} });

      // Construct answer
      PointEquation point_composition3_image({ complex{-1,0}, complex{7, 0}, complex{1, 0} });

      // Check transformation
      EXPECT_TRUE(check_two_coordinates(composition3(point_composition3.equation), point_composition3_image.equation, epsilon));
    }

    TEST(Transformation, Multiplication)
    {
      // Create random matrix
      const Transformation transformation(TransformationMatrix(
        complex(-4.924, -2.768),
        complex(0.248, 9.890),
        complex(2.895, 8.700),

        complex(-5.526, -0.244),
        complex(5.526, -3.827),
        complex(-7.857, 1.492),

        complex(7.554, 2.673),
        complex(-9.136, -7.834),
        complex(2.573, 0.384)
      ));

      // Create random point
      const HomogeneousCoordinate point
      {
        complex(-2.728, 2.730),
        complex(8.852, -2.598),
        complex(-2.883, 6.312)
      };

      // Check Id transform
      EXPECT_TRUE(check_two_coordinates(Transformation() * point, point, epsilon));

      // {-2.728+2.730*i,8.852-2.598*i,-2.883+6.312*i}

      // Create real answer to transformation * point
      const HomogeneousCoordinate answer
      {
        complex(-14.38185700, 74.2017000),
        complex(67.94888100, -116.54832000),
        complex(-138.97097300, -17.14706000)
      };

      // Check answer
      EXPECT_TRUE(check_two_coordinates(transformation * point, answer, epsilon));

      // Create zero point
      const HomogeneousCoordinate zero_coord
      {
        complex(0),
        complex(0),
        complex(0)
      };

      // Check transform of zero point
      EXPECT_TRUE(check_two_coordinates(transformation * zero_coord, zero_coord, epsilon));

      // Create zero transformation
      const Transformation zero_trans(TransformationMatrix(
        complex(0),
        complex(0),
        complex(0),

        complex(0),
        complex(0),
        complex(0),

        complex(0),
        complex(0),
        complex(0)
      ));

      // Check zero transformation
      EXPECT_TRUE(check_two_coordinates(zero_trans * point, zero_coord, epsilon));
    }
  }

  namespace Equation
  {
    /// TODO (Write tests)
  }

  namespace GeometricObjectFactory
  {
    /// TODO (Write tests)
  }

  namespace GeometricObjectImplementation
  {
    /// TODO (Write tests)
  }

  namespace PlaneImplementation
  {
    /// TODO (Write tests)
  }
}
