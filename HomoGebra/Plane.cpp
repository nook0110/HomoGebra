#include "Plane.h"

#include "Construction.h"
#include "GeometricObject.h"

void Plane::AddConstruction(std::unique_ptr<Construction> construction)
{
  // Add object to plane
  implementation_.AddConstruction(std::move(construction));
}

template <class GeometricObjectType>
std::vector<GeometricObject*> Plane::GetObjects() const
{
  return implementation_.GetObjects<GeometricObjectType>();
}

template std::vector<GeometricObject*> Plane::GetObjects<GeometricObject>()
    const;

template std::vector<GeometricObject*> Plane::GetObjects<Point>() const;

template std::vector<GeometricObject*> Plane::GetObjects<Line>() const;

template std::vector<GeometricObject*> Plane::GetObjects<Conic>() const;

void Plane::Update(const sf::Event& event)
{
  // Update plane body
  body_.Update(event);
}

void Plane::Update(sf::RenderTarget& target) const
{
  // Update all objects
  for (const auto& object : GetObjects<GeometricObject>())
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
  for (const auto& object : GetObjects<GeometricObject>())
  {
    target.draw(*object, states);
  }
}

const NameGenerator& Plane::GetNameGenerator() const
{
  return implementation_.GetNameGenerator();
}