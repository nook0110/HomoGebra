#include "Plane.h"

#include <algorithm>

#include "Construction.h"
#include "GeometricObject.h"

namespace HomoGebra
{
void Plane::AddConstruction(std::unique_ptr<Construction> construction)
{
  // Add object to plane
  implementation_.AddConstruction(std::move(construction));
}

void Plane::DeleteObject(const GeometricObject* object)
{
  implementation_.DestroyObject(object);
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

void Plane::UpdateBodies(const sf::RenderTarget& target) const
{
  // Update all objects
  std::ranges::for_each(GetObjects<GeometricObject>(),
                        [&target](const auto object)
                        { object->UpdateBody(target); });
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  //  Draw all objects
  std::ranges::for_each(GetObjects<GeometricObject>(),
                        [&target, &states](const auto object)
                        { target.draw(*object, states); });
}

void Plane::Update(const UserEvent::Click& clicked_event)
{
  EventNotifier::Notify(clicked_event);
}

const NameGenerator& Plane::GetNameGenerator() const
{
  return implementation_.GetNameGenerator();
}

void Plane::Attach(PlaneObserver* observer)
{
  implementation_.Attach(observer);
}

void Plane::Detach(const PlaneObserver* observer)
{
  implementation_.Detach(observer);
}
}  // namespace HomoGebra