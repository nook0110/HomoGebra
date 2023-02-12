#include "pch.h"

#include "../HomoGebra/Coordinate.h"
#include "../HomoGebra/Coordinate.cpp"
#include "../HomoGebra/Equation.h"
#include "../HomoGebra/Equation.cpp"
#include "../HomoGebra/GeometricObjectImplementation.h"
#include "../HomoGebra/GeometricObjectImplementation.cpp"

namespace HomoGebra
{
  namespace Coordinate
  {
    TEST(TransformationMatrix, Determinant)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      auto inverse = identity.Determinant();

      TransformationMatrix random_matrix(
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
      {{-4.924+i*-2.768, 0.248+i*9.890, 2.895+i*8.700},
      {-5.526+i*-0.244, 5.526+i*-3.827, -7.857+i*1.492},
      {7.554+i*2.673, -9.136+i*-7.834, 2.573+i*0.384}}
      determinant is about -292.293 + 116.289*i
      */

      auto det = random_matrix.Determinant();
      ASSERT_NEAR(det.real(), -292.293300759, 0.0000001);
      ASSERT_NEAR(det.imag(), 116.289449988, 0.0000001);
    }

    TEST(TransformationMatrix, Inverse)
    {
      // Create an identity matrix
      TransformationMatrix identity;

      //auto inverse = identity.GetInverse();
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

TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}