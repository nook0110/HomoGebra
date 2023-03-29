#include "Plane.h"

void Plane::AddObject(const std::shared_ptr<GeometricObject>& object)
{
  // Add object to plane
  implementation_.AddObject(object);
}

const std::vector<std::shared_ptr<GeometricObject>>& Plane::GetObjects() const
{
  // Return all objects
  return implementation_.GetObjects();
}

std::vector<std::shared_ptr<GeometricObject>> Plane::GetPoints() const
{
  return implementation_.GetPoints();
}

std::vector<std::shared_ptr<GeometricObject>> Plane::GetLines() const
{
  return implementation_.GetLines();
}

std::vector<std::shared_ptr<GeometricObject>> Plane::GetConics() const
{
  return implementation_.GetConics();
}

void Plane::Update(sf::RenderTarget& target)
{
  // Update all objects
  for (const auto& object : implementation_.GetObjects())
  {
    object->UpdateBody(target);
  }
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // body_.Draw(target, states);
  //  Draw all objects
  for (const auto& object : implementation_.GetObjects())
  {
    target.draw(*(object.get()), states);
  }
}