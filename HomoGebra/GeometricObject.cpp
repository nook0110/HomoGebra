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

void Point::Notify(const Event::Renamed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}

float Point::CalculateSizeOfBody(const sf::RenderTarget& target)
{
  // Calculate position of pixel with coordinate (0, 0)
  const auto first_pixel_position = target.mapPixelToCoords({0, 0});

  // Calculate position of pixel with coordinate (1, 0)
  const auto second_pixel_position = target.mapPixelToCoords({1, 0});

  // Calculate size of pixel
  const auto pixel_size =
      std::abs(second_pixel_position.x - first_pixel_position.x);

  // Ratio of size of body to size of pixel
  constexpr float kRatio = 6.28318530718f;

  // Calculate size of body
  const auto size = pixel_size * kRatio;

  // Return size of body
  return size;
}

void Point::SetEquation(const PointEquation& equation)
{
  // Set equation in implementation
  implementation_.SetEquation(equation);

  // Update body
  body_.Update(equation);
}

const PointEquation& Point::GetEquation() const
{
  // Return equation
  return implementation_.GetEquation();
}

void Point::Attach(std::shared_ptr<GeometricObjectObserver> observer)
{
  // Call implementation method
  implementation_.Attach(observer);
}

void Point::UpdateBody(sf::RenderTarget& target)
{
  // Calculate size of body
  const float size = CalculateSizeOfBody(target);

  // Update body
  body_.Update(implementation_.GetEquation(), size);
}

void Point::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(body_, states);
}

void Point::SetName(const std::string& name)
{
  Notify(Event::Renamed{this, body_.GetName(), name});

  body_.SetName(name);
}

const std::string& Point::GetName() const
{
  // Return name
  return body_.GetName();
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

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // body_.Draw(sf::RenderTarget & target, sf::RenderStates states);
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

void Conic::draw(sf::RenderTarget& target, sf::RenderStates states) const {}