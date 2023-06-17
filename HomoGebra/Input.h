#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include "EventNotifier.h"
#include "ObjectProvider.h"

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
class NearbyObjectGetter : public EventListener
{
 public:
  /**
   * \brief Constructor.
   *
   * \param plane Plane, where the object is located.
   * \param window Render window.
   * \param last_object Last object that user clicked on.
   */
  explicit NearbyObjectGetter(Plane& plane, sf::RenderWindow& window,
                              GeometricObjectType* last_object = nullptr);

  /**
   * \brief Gets the last object that user clicked on.
   *
   * \return Last object that user clicked on.
   */
  GeometricObjectType* GetLastObject();

  /**
   * \brief Rests current object.
   */
  void Reset();

  /**
   * \brief Sets current object.
   *
   * \param object Object to set.
   */
  void SetObject(GeometricObjectType* object);

  void Update(const UserEvent::Clicked& event) override;

 private:
  /**
   * \brief Finds the nearest object to the mouse.
   *
   */
  void FindNearestObject(const sf::Vector2f& position);

  sf::RenderWindow& window_;  //!< Render window.

  GeometricObjectType* last_object_;  //!< Last object that user clicked on.

  ObjectProvider finder_;  //!< Helper to find objects.
};
