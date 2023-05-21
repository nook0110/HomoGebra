#include "GeometricObjectBody.h"

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <cassert>

#include "Helpers.h"

ObjectName::ObjectName(const std::string& name)
{
  // Load font
  font_.loadFromFile(kFontPath);

  // Set font
  text_.setFont(font_);
  text_.setCharacterSize(kCharacterSize);

  // Set color
  text_.setFillColor(kTextColor);

  // Set name
  SetName(name);
}

void ObjectName::SetName(const std::string& name)
{
  name_ = name;
  text_.setString(name);
}

const std::string& ObjectName::GetName() const { return name_; }

void ObjectName::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Apply transform
  states.transform *= getTransform();
  // Draw
  target.draw(text_, states);
}

PointBody::PointBody() { body_.setFillColor(sf::Color::Red); }

void PointBody::SetName(const std::string& name) { text_.SetName(name); }

const std::string& PointBody::GetName() const { return text_.GetName(); }

void PointBody::Update(const PointEquation& equation, const float size)
{
  // Calculate position
  position_ = CalculatePosition(equation);

  if (position_)
  {
    body_.setPosition(position_.value().position);
    text_.setPosition(position_.value().position);
  }

  // Set size
  body_.setRadius(size);
  body_.setOrigin(size, size);
}

void PointBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!position_) return;

  if (const auto& [position, is_at_infinity] = position_.value();
      is_at_infinity)
  {
    // Draw point at infinity
    DrawArrow(target, states);
  }
  else
  {
    // Draw point
    target.draw(body_, states);
    target.draw(text_, states);
  }
}

void PointBody::DrawArrow(sf::RenderTarget& target,
                          sf::RenderStates states) const
{
  assert(position_);

  const auto& [position, is_at_infinity] =
      position_.value();  // NOLINT(bugprone-unchecked-optional-access)

  assert(is_at_infinity);

  const auto& view = target.getView();
  const auto intersection = Helpers::IntersectRayWithRectangle(
      view.getCenter(), position, view.getViewport());

  assert(intersection.has_value());

  // Coefficient for start of line.
  constexpr auto kStartShift = 0.9f;
  const auto arrow_start = intersection.value() * kStartShift +
                           view.getCenter() * (1.f - kStartShift);
  constexpr auto kEndShift = 0.95f;
  const auto arrow_end =
      intersection.value() * kEndShift + view.getCenter() * (1.f - kEndShift);

  thor::Arrow arrow{arrow_start, arrow_end, sf::Color::Black, 10};
}

std::optional<PointBody::ProjectivePosition> PointBody::CalculatePosition(
    const PointEquation& equation)
{
  // Get equation
  const auto& eq = equation.GetEquation();

  // Normalize equation
  const auto normalized_eq = eq.GetNormalized();

  // Check if point lies on the "R-plane" which we see
  if (!IsReal(normalized_eq.x) || !IsReal(normalized_eq.y))
  {
    return std::nullopt;
  }

  // Check if point is at infinity
  if (IsZero(normalized_eq[Var::kZ]))
  {
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

void LineBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {}