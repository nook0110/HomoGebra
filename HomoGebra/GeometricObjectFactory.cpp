#include "GeometricObjectFactory.h"

#include <cassert>

#include "Matrix.h"
#include "ObjectConstruction.h"

PointFactory::PointFactory(Plane& plane) : plane_(plane) {}

Point* PointFactory::OnPlane(PointEquation equation)
{
  // Create construction
  auto construction = std::make_unique<PointOnPlane>(std::move(equation));

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

Line* LineFactory::OnPlane(LineEquation equation)
{
  // Create construction
  auto construction = std::make_unique<LineOnPlane>(std::move(equation));

  const auto line = construction->GetLine();

  // Add construction to plane
  plane_.AddConstruction(std::move(construction));

  const auto& name_generator = plane_.GetNameGenerator();

  // Rename line
  // line->SetName(static_cast<std::string>(
  //     name_generator.GenerateName(first->GetName() + second->GetName())));

  // Return line
  return line;
}

Line* LineFactory::ByTwoPoints(Point* first, Point* second)
{
  // Create construction
  auto construction = std::make_unique<class ByTwoPoints>(first, second);

  const auto line = construction->GetLine();

  // Add line to plane
  plane_.AddConstruction(std::move(construction));

  const auto& name_generator = plane_.GetNameGenerator();

  line->SetName(static_cast<std::string>(
      name_generator.GenerateName(first->GetName() + second->GetName())));

  // Return line
  return line;
}

ConicFactory::ConicFactory(Plane& plane) : plane_(plane) {}

Conic* ConicFactory::OnPlane(ConicEquation equation)
{
  // Create construction
  auto construction = std::make_unique<ConicOnPlane>(std::move(equation));

  const auto conic = construction->GetConic();

  // Add construction to plane
  plane_.AddConstruction(std::move(construction));

  const auto& name_generator = plane_.GetNameGenerator();

  // Rename conic
  conic->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return conic
  return conic;
}

Conic* ConicFactory::ByFivePoints(Point* first, Point* second, Point* third,
                                  Point* fourth, Point* fifth)
{
  assert(false);
  return nullptr;
}