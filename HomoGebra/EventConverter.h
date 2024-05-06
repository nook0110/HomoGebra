#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <Thor/Input.hpp>

#include "EventNotifier.h"

namespace HomoGebra
{
class EventConverter : public EventNotifier
{
 public:
  explicit EventConverter(sf::RenderWindow* window);

  void Update(const sf::Event& event);

  enum class Action
  {
    Click,
    Unclick
  };

 private:
  using ActionMap = thor::ActionMap<Action>;
  using ActionContext = thor::ActionContext<Action>;
  using CallbackSystem = ActionMap::CallbackSystem;

  void InitActionMap();
  void InitCallbackSystem();

  void OnClick(ActionContext context) const;

  ActionMap actionMap_;
  CallbackSystem system_;
  sf::RenderWindow* window_;
};
}  // namespace HomoGebra
