#include "GeometricObject.h"

Point::Point(const PointEquation& equation)
{
}

Point::~Point()
{
  // Notify observers that object was destroyed
  //Notify(Event::Destroyed{ plane_ });
}

void Point::SetEquation(const PointEquation& equation)
{

}

const PointEquation& Point::GetEquation() const
{
  // Return equation
  return implementation_.GetEquation();
}

Line::Line(const LineEquation& equation)
{
}

void Line::SetEquation(const LineEquation& equation)
{
}
