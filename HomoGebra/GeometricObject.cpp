#include "GeometricObject.h"

Point::~Point()
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{ plane_ });
}
