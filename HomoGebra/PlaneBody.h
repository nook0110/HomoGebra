#pragma once
#include <SFML/Graphics.hpp>

class PlaneBody final : public sf::Drawable
{
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Update(const sf::Event& event);

  const sf::View& GetView() const;

 private:
  void MouseEventUpdate(const sf::Event& event);

  sf::View view_;
};
