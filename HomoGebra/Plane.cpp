#include "Plane.h"

#include "GeometricObject.h"

void Plane::AddObject(const std::shared_ptr<GeometricObject>& object)
{
  // Add object to plane
  implementation_.AddObject(object);
}

template <class GeometricObjectType>
std::vector<std::shared_ptr<GeometricObject>> Plane::GetObjects() const
{
  return implementation_.GetObjects<GeometricObjectType>();
}

template std::vector<std::shared_ptr<GeometricObject>>
Plane::GetObjects<GeometricObject>() const;

template std::vector<std::shared_ptr<GeometricObject>>
Plane::GetObjects<Point>() const;

template std::vector<std::shared_ptr<GeometricObject>> Plane::GetObjects<Line>()
    const;

template std::vector<std::shared_ptr<GeometricObject>>
Plane::GetObjects<Conic>() const;

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

void Plane::Update(const sf::Event& event)
{
  // Update plane body
  body_.Update(event);
}

void Plane::Update(sf::RenderTarget& target) const
{
  // Update all objects
  for (const auto& object : implementation_.GetObjects())
  {
    object->UpdateBody(target);
  }
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(body_, states);

  // Set view
  target.setView(body_.GetView());

  //  Draw all objects
  for (const auto& object : implementation_.GetObjects())
  {
    target.draw(*object.get(), states);
  }
}

const NameGenerator& Plane::GetNameGenerator() const
{
  return implementation_.GetNameGenerator();
}