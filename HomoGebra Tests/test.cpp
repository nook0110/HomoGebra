#include "pch.h"

#include "../HomoGebra/Coordinate.h"
#include "../HomoGebra/Coordinate.cpp"
#include "../HomoGebra/Equation.h"
#include "../HomoGebra/Equation.cpp"
#include "../HomoGebra/GeometricObjectImplementation.h"
#include "../HomoGebra/GeometricObjectImplementation.cpp"

namespace HomoGebra
{
  constexpr long double epsilon = 1e-6L;


  namespace Coordinate
  {
    void check_two_complex(const complex& first, const complex& second, long double abs_error)
    {
      ASSERT_NEAR(first.real(), second.real(), abs_error);
      ASSERT_NEAR(first.imag(), second.imag(), abs_error);
    }

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

      auto det = matrix.Determinant();

      check_two_complex(det, complex { -292.293300759 , 116.289449988 }, epsilon);
    }

    TEST(TransformationMatrix, Inverse)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      auto inverse_of_identity = identity.GetInverse();

      ASSERT_TRUE(inverse_of_identity.has_value());

      check_two_matrix(identity, inverse_of_identity.value(), epsilon);


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

      auto inverse = matrix.GetInverse();

      auto correct_inverse = TransformationMatrix(
        complex(0.134816, 0.244013),
        complex(-0.282593, 0.324476),
        complex(0.060579, 0.415259),
        complex(0.137162, 0.0784553),
        complex(-0.0667268, 0.255604),
        complex(0.0932031, 0.253248),
        complex(0.0801455, -0.172217),
        complex(0.154899, 0.0222525),
        complex(0.183203, -0.126436)
      );

      ASSERT_TRUE(inverse.has_value());

      check_two_matrix(correct_inverse, inverse.value(), epsilon);
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