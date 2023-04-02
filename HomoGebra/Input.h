#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include "GeometricObject.h"
#include "GeometricObjectFactory.h"

/**
 * \brief Gets the last object that user clicked on.
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
  explicit NearbyObjectGetter(
      Plane& plane, sf::RenderWindow& window,
      std::shared_ptr<GeometricObjectType> last_object = nullptr);

  std::shared_ptr<GeometricObjectType> GetLastObject();

  void Update(const sf::Event& event);

 private:
  enum class Action
  {
    kClick
  };

  /**
   * \brief Initializes the action map.
   *
   */
  void InitActionMap();

  void FindNearestObject();

  thor::ActionMap<Action> action_map_;  //!< Map with actions that user do.

  sf::RenderWindow& window_;

  std::shared_ptr<GeometricObjectType> last_object_;

  ConstructedObjectFactory factory_;
};
