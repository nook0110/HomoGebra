#include "GeometricObject.h"

#include <utility>

#include "Equation.h"
#include "GeometricObjectImplementation.h"

Point::Point(PointEquation equation) : implementation_(std::move(equation)) {}

void Point::Destroy()
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this});
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

void Point::SetEquation(PointEquation equation)
{
  // Set equation in implementation
  implementation_.SetEquation(std::move(equation));

  // Update body
  body_.Update(implementation_.GetEquation());
}

const PointEquation& Point::GetEquation() const
{
  // Return equation
  return implementation_.GetEquation();
}

void Point::Attach(GeometricObjectObserver* observer)
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

void Point::SetName(std::string name)
{
  const Event::Renamed renamed{this, body_.GetName(), name};

  body_.SetName(std::move(name));

  Notify(renamed);
}

const std::string& Point::GetName() const
{
  // Return name
  return body_.GetName();
}

Line::Line(LineEquation equation) : implementation_(std::move(equation)) {}

void Line::Destroy()
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this});
}

void Line::Notify(const Event::Destroyed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}

void Line::SetEquation(LineEquation equation)
{
  // Set equation in implementation
  implementation_.SetEquation(std::move(equation));
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

Conic::Conic(ConicEquation equation) : implementation_(std::move(equation)) {}

void Conic::Destroy()
{
  // Notify observers that object was destroyed
  Notify(Event::Destroyed{this});
}

void Conic::Notify(const Event::Destroyed& event) const
{
  // Call implementation method
  implementation_.Notify(event);
}

void Conic::UpdateBody(sf::RenderTarget& target)
{
  body_.Update(implementation_.GetEquation());
}

void Conic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(body_, states);
}