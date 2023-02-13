#include "pch.h"

#include "../HomoGebra/Coordinate.h"
#include "../HomoGebra/Coordinate.cpp"
#include "../HomoGebra/Equation.h"
#include "../HomoGebra/Equation.cpp"
#include "../HomoGebra/GeometricObjectImplementation.h"
#include "../HomoGebra/GeometricObjectImplementation.cpp"

namespace HomoGebra
{
  constexpr long double epsilon = 1e-10L;

  namespace Coordinate
  {
    // Checks that two complex number are equal with precision [abs_error]
    void check_two_complex(const complex& first, const complex& second, long double abs_error)
    {
      EXPECT_NEAR(first.real(), second.real(), abs_error);
      EXPECT_NEAR(first.imag(), second.imag(), abs_error);
    }

    // Checks that two matrices are equal [each element] with precision [abs_error]
    void check_two_matrix(const TransformationMatrix& first, const TransformationMatrix& second, long double abs_error)
    {
      for (int row = 0; row < std::tuple_size<TransformationMatrix::MatrixColumn>::value; ++row)
      {
        for (int column = 0; column < std::tuple_size<TransformationMatrix::MatrixColumn>::value; ++column)
        {
          check_two_complex(first[row][column], second[row][column], abs_error);
        }
      }
    }

    TEST(TransformationMatrix, Determinant)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      // Create a random matrix
      TransformationMatrix matrix(
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

      /*
      {{-4.924+i*-2.768, 0.248+i*9.890, 2.895+i*8.700},{-5.526+i*-0.244, 5.526+i*-3.827, -7.857+i*1.492},{7.554+i*2.673, -9.136+i*-7.834, 2.573+i*0.384}}
      determinant is about complex { -292.293300759 , 116.289449988 }
      */

      // Compute determinant
      auto det = matrix.Determinant();

      // Check answer
      check_two_complex(det, complex { -292.293300759 , 116.289449988 }, epsilon);
    }

    TEST(TransformationMatrix, Inverse)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      // Find inverse matrix
      auto inverse_of_identity = identity.GetInverse();

      // Check existing
      ASSERT_TRUE(inverse_of_identity.has_value());

      // Check answer
      check_two_matrix(identity, inverse_of_identity.value(), epsilon);

      // Create a random matrix
      TransformationMatrix matrix(
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
      auto inverse = matrix.GetInverse();

      // Check existing
      ASSERT_TRUE(inverse.has_value());

      // Construct answer
      auto correct_inverse = TransformationMatrix(
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
      check_two_matrix(correct_inverse, inverse.value(), epsilon);
    }

    TEST(TransformationMatrix, Multiplication)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      // Create a random matrix
      TransformationMatrix matrix(
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
      check_two_matrix(matrix * identity, matrix, epsilon);
      check_two_matrix(identity * matrix, matrix, epsilon);
      check_two_matrix(identity * identity, identity, epsilon);

      // Compute inverse
      auto inverse = matrix.GetInverse();

      // Checks A*A^-1 = E = A^-1*A
      check_two_matrix(matrix * inverse.value(), identity, epsilon);
      check_two_matrix(inverse.value() * matrix, identity, epsilon);

      // Create matrix^2
      TransformationMatrix squared_matrix(
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
      check_two_matrix(matrix * matrix, squared_matrix, epsilon);
      check_two_matrix(squared_matrix * inverse.value(), matrix, epsilon);
      check_two_matrix(inverse.value() * squared_matrix, matrix, epsilon);
    }
  }

  namespace Equation
  {

  }

  namespace GeometricObjectFactory
  {

  }

  namespace GeometricObjectImplementation
  {

  }

  namespace PlaneImplementation
  {

  }
}