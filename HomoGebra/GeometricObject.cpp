#include "GeometricObject.h"

Point::Point(const PointEquation& equation) : implementation_(equation) {}

void Point::Destroy(Plane& plane)
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this, plane});
}

void Point::Notify(const Event::Destroyed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}

void Point::SetEquation(const PointEquation& equation)
{
  // Set equation in implementation
  implementation_.SetEquation(equation);
}

const PointEquation& Point::GetEquation() const
{
  // Return equation
  return implementation_.GetEquation();
}

Line::Line(const LineEquation& equation) : implementation_(equation) {}

void Line::Destroy(Plane& plane)
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this, plane});
}

void Line::Notify(const Event::Destroyed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}

void Line::SetEquation(const LineEquation& equation)
{
  // Set equation in implementation
  implementation_.SetEquation(equation);
}

const LineEquation& Line::GetEquation() const
{
  // Return equation
  return implementation_.GetEquation();
}

Conic::Conic(const ConicEquation& equation) : implementation_(equation) {}

void Conic::Destroy(Plane& plane)
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this, plane});
}

void Conic::Notify(const Event::Destroyed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}