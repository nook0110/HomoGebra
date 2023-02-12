#pragma once
#include "PlaneImplementation.h"
#include "PlaneBody.h"

/**
 * \brief Container for all objects, which you can draw.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PlaneImplementation
 * \see PlaneBody
 */
class Plane
{
private:
  PlaneImplementation implementation_;
  PlaneBody body_;
};
