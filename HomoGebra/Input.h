#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include "GeometricObject.h"
#include "PlaneHelper.h"

/**
 * \brief Class to get the last object that user clicked on.
 *
 * \tparam GeometricObjectType Type of the geometric object.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
template <class GeometricObjectType>
class NearbyObjectGetter
{
 public:
  /**
   * \brief Constructor.
   *
   * \param plane Plane, where the object is located.
   * \param window Render window.
   * \param last_object Last object that user clicked on.
   */
  explicit NearbyObjectGetter(
      Plane& plane, sf::RenderWindow& window,
      std::shared_ptr<GeometricObjectType> last_object = nullptr);

  /**
   * \brief Gets the last object that user clicked on.
   *
   * \return Last object that user clicked on.
   */
  std::shared_ptr<GeometricObjectType> GetLastObject();

  /**
   * \brief Updates the object.
   *
   * \param event Event that user've done.
   */
  void Update(const sf::Event& event);

 private:
  /**
   * \enum Action Actions that user do.
   *
   * \var Action::kClick
   * Action showing that user clicked.
   */
  enum class Action
  {
    kClick
  };

  /**
   * \brief Initializes the action map.
   *
   */
  void InitActionMap();

  /**
   * \brief Finds the nearest object to the mouse.
   *
   */
  void FindNearestObject();

  thor::ActionMap<Action> action_map_;  //!< Map with actions that user do.

  sf::RenderWindow& window_;  //!< Render window.

  std::shared_ptr<GeometricObjectType>
      last_object_;  //!< Last object that user clicked on.

  PlaneHelper finder_;  //!< Helper to find objects.
};
