#include "GeometricObjectFactory.h"

#include "Matrix.h"
#include "ObjectConstruction.h"

namespace HomoGebra
{
Point* PointOnPlaneFactory::operator()(PointEquation equation) const
{
  // Create construction
  auto construction = std::make_unique<PointOnPlane>(std::move(equation));

  const auto point = construction->GetPoint();

  // Add construction to plane
  plane_->AddConstruction(std::move(construction));

  const auto& name_generator = plane_->GetNameGenerator();

  // Rename point
  point->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return point
  return point;
}

Line* LineOnPlaneFactory::operator()(LineEquation equation) const
{
  // Create construction
  auto construction = std::make_unique<LineOnPlane>(std::move(equation));

  const auto line = construction->GetLine();

  // Add construction to plane
  plane_->AddConstruction(std::move(construction));

  const auto& name_generator = plane_->GetNameGenerator();

  // Rename line
  line->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return line
  return line;
}

Line* LineByTwoPointsFactory::operator()(Point* first, Point* second) const
{
  // Create construction
  auto construction = std::make_unique<class ByTwoPoints>(first, second);

  const auto line = construction->GetLine();

  // Add line to plane
  plane_->AddConstruction(std::move(construction));

  const auto& name_generator = plane_->GetNameGenerator();

  line->SetName(static_cast<std::string>(
      name_generator.GenerateName(first->GetName() + second->GetName())));

  // Return line
  return line;
}

Conic* ConicOnPlaneFactory::operator()(ConicEquation equation) const
{
  // Create construction
  auto construction = std::make_unique<ConicOnPlane>(std::move(equation));

  const auto conic = construction->GetConic();

  // Add construction to plane
  plane_->AddConstruction(std::move(construction));

  const auto& name_generator = plane_->GetNameGenerator();

  // Rename conic
  conic->SetName(static_cast<std::string>(name_generator.GenerateName()));

  // Return conic
  return conic;
}
}  // namespace HomoGebra