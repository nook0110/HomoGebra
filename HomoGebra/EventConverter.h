#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <Thor/Input.hpp>

#include "EventNotifier.h"

namespace HomoGebra
{
/**
 * @brief The EventConverter class is responsible for converting SFML events
 * into custom actions.
 *
 * It inherits from the EventNotifier class and provides functionality to handle
 * events such as clicks and unclicks.
 */
class EventConverter : public EventNotifier
{
 public:
  /**
   * @brief Constructs an EventConverter object with the specified SFML render
   * window.
   *
   * @param window A pointer to the SFML render window.
   */
  explicit EventConverter(sf::RenderWindow* window);

  /**
   * @brief Updates the EventConverter with the specified SFML event.
   *
   * @param event The SFML event to update with.
   */
  void Update(const sf::Event& event);

  /**
   * @brief The Action enum class represents the custom actions that can be
   * triggered by events.
   */
  enum class Action
  {
    Click,  /**< Represents a click action. */
    Unclick /**< Represents an unclick action. */
  };

 private:
  using ActionMap = thor::ActionMap<Action>;
  using ActionContext = thor::ActionContext<Action>;
  using CallbackSystem = ActionMap::CallbackSystem;

  /**
   * @brief Initializes the action map for handling custom actions.
   */
  void InitActionMap();

  /**
   * @brief Initializes the callback system for handling custom actions.
   */
  void InitCallbackSystem();

  /**
   * @brief Handles the click action.
   *
   * @param context The action context for the click action.
   */
  void OnClick(ActionContext context) const;

  ActionMap actionMap_; /**< The action map for handling custom actions. */
  CallbackSystem
      system_; /**< The callback system for handling custom actions. */
  sf::RenderWindow* window_; /**< A pointer to the SFML render window. */
};
}  // namespace HomoGebra
