#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

using Distance = float;

inline Distance Length(const sf::Vector2f& vector)
{
  return std::hypot(vector.x, vector.y);
}

inline Distance DistanceToLine(const sf::Vector2f& position, const float a,
                               const float b, const float c)
{
  return std::abs(a * position.x + b * position.y + c) /
         (std::sqrt(a * a + b * b));
}
