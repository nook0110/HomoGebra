#pragma once
#include <SFML/Graphics.hpp>

class PlaneBody final : public sf::Drawable
{
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
