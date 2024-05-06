#include "EventConverter.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Assert.h"
namespace HomoGebra
{
EventConverter::EventConverter(sf::RenderWindow* window) : window_(window)
{
  InitActionMap();
  InitCallbackSystem();
}

void EventConverter::Update(const sf::Event& event)
{
  actionMap_.clearEvents();
  actionMap_.pushEvent(event);
  actionMap_.invokeCallbacks(system_, window_);
}

void EventConverter::InitActionMap()
{
  actionMap_[Action::Click] =
      thor::Action{sf::Mouse::Left, thor::Action::PressOnce};
  actionMap_[Action::Unclick] =
      thor::Action{sf::Mouse::Left, thor::Action::ReleaseOnce};
}
void EventConverter::InitCallbackSystem()
{
  system_.connect(Action::Click, [this](ActionContext context)
                  { OnClick(std::move(context)); });
}

void EventConverter::OnClick(ActionContext context) const
{
  const auto& [window, event, action_id] = context;
  Assert(action_id == Action::Click);
  Assert(dynamic_cast<sf::RenderWindow*>(window));

  auto click_position =
      static_cast<sf::RenderWindow*>(window)->mapPixelToCoords(
          sf::Vector2i{event->mouseButton.x, event->mouseButton.y});

  Notify(UserEvent::Click{click_position});
}
}  // namespace HomoGebra