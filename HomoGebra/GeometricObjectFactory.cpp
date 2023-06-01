#include "GeometricObjectFactory.h"

#include <cassert>

#include "Matrix.h"
#include "ObjectConstruction.h"

PointFactory::PointFactory(Plane& plane) : plane_(plane) {}

Point* PointFactory::OnPlane(const PointEquation& coordinate)
{
  // Create construction
  auto construction = std::make_unique<ConstructionOnPlane>(coordinate);

  const auto point = construction->GetPoint();

  // Add construction to plane
  plane_.AddConstruction(std::move(construction));

  const auto& name_generator = plane_.GetNameGenerator();

  // Rename point
  point->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return point
  return point;
}

Point* PointFactory::Projection(Point* from, Line* to) { return nullptr; }

LineFactory::LineFactory(Plane& plane) : plane_(plane) {}

Line* LineFactory::ByTwoPoints(Point* first, Point* second)
{
  // Create construction
  auto construction = std::make_unique<class ByTwoPoints>(first, second);

  const auto line = construction->GetLine();

  // Add line to plane
  plane_.AddConstruction(std::move(construction));

  // Return line
  return line;
}

ConicFactory::ConicFactory(Plane& plane) : plane_(plane) {}

Conic* ConicFactory::OnPlane(const ConicEquation& equation)
{
  assert(false);
  return nullptr;
}

Conic* ConicFactory::ByFivePoints(Point* first, Point* second, Point* third,
                                  Point* fourth, Point* fifth)
{
  assert(false);
  return nullptr;
}