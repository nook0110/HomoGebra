#include "PlaneBody.h"

void PlaneBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

void PlaneBody::Update(const sf::Event& event) { MouseEventUpdate(event); }

const sf::View& PlaneBody::GetView() const
{
  // Return view
  return view_;
}

void PlaneBody::MouseEventUpdate(const sf::Event& event)
{
  // Check if mouse button was pressed
  if (event.type == sf::Event::MouseWheelScrolled)
  {
    // Zoom factor
    constexpr float kZoom = 1.1f;

    // Zoom in or out
    if (event.mouseWheelScroll.delta > 0)
    {
      view_.zoom(1 / kZoom);
    }
    else if (event.mouseWheelScroll.delta < 0)
    {
      view_.zoom(kZoom);
    }
  }
}