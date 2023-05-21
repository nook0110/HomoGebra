// TODO: Rename file

#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

#include "Matrix.h"

// TODO: Rename namespace
namespace Helpers
{
inline [[nodiscard]] std::optional<sf::Vector2f> IntersectRayWithRectangle(
    const sf::Vector2f& point, const sf::Vector2f& direction,
    const sf::FloatRect& rectangle)
{
  if (!rectangle.contains(point))
  {
    return std::nullopt;
  }

  // TODO: Intersect line with rect.

  struct Line
  {
    float a;
    float b;
    float c;

    Line(sf::Vector2f first_point, sf::Vector2f second_point)
    {
      FloatSquaredMatrix matrix({{first_point.x, first_point.y, 1},
                                 {second_point.x, second_point.y, 1},
                                 {1, 1, 1}},
                                {0, 0, 1});
      auto solution = matrix.GetSolution();
    }
  };
}
}  // namespace Helpers
