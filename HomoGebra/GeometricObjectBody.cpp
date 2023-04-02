#include "GeometricObjectBody.h"

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>

PointBody::PointBody() { body_.setFillColor(sf::Color::Red); }

void PointBody::SetName(const std::string& name)
{
  name_ = name;
  text_.setString(name);
}

const std::string& PointBody::GetName() const { return name_; }

void PointBody::Update(const PointEquation& equation, const float size)
{
  // Calculate position
  position_ = CalculatePosition(equation);

  if (position_)
  {
    body_.setPosition(position_.value().position);
  }

  // Set size
  body_.setRadius(size);
  body_.setOrigin(size, size);
}

void PointBody::draw(sf::RenderTarget& target, sf::RenderStates) const
{
  if (!position_) return;

  if (const auto& [position, is_at_infinity] = position_.value();
      is_at_infinity)
  {
    // Draw point at infinity
    thor::Arrow arrow;
    arrow.setDirection(position * 100.f);
    target.draw(arrow);
  }
  else
  {
    // Draw point
    target.draw(body_);
  }
}

std::optional<PointBody::ProjectivePosition> PointBody::CalculatePosition(
    const PointEquation& equation)
{
  // Get equation
  const auto& eq = equation.GetEquation();

  // Normalize equation
  const auto normalized_eq = eq.GetNormalized();

  // Check if point is at infinity
  if (IsZero(normalized_eq[Var::kZ]))
  {
    // Check if point lies on the "R-plane" which we see
    if (!IsReal(normalized_eq.x)) return std::nullopt;

    return ProjectivePosition{
        sf::Vector2f(static_cast<float>(normalized_eq.x.real()),
                     static_cast<float>(normalized_eq.y.real())),
        true};
  }

  // Return position
  return ProjectivePosition{
      sf::Vector2f(static_cast<float>(normalized_eq.x.real()),
                   static_cast<float>(normalized_eq.y.real())),
      false};
}