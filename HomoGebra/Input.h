#pragma once
#include "EventNotifier.h"
#include "ObjectProvider.h"

namespace HomoGebra
{
/**
 * \brief Class to get the last object that user clicked on.
 *
 * \tparam GeometricObjectType Type of the geometric object.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date April 2023
 */
template <class GeometricObjectType>
class NearbyObjectGetter final : public EventListener
{
 public:
  /**
   * \brief Constructor.
   *
   * \param plane Plane, where the object is located.
   * \param last_object Last object that user clicked on.
   */
  explicit NearbyObjectGetter(Plane* plane,
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

  void Update(const UserEvent::Click& event) override;

 private:
  /**
   * \brief Finds the nearest object to the mouse.
   *
   * \param position Position of the mouse.
   */
  void FindNearestObject(const sf::Vector2f& position);

  GeometricObjectType* last_object_;  //!< Last object that user clicked on.

  ObjectProvider finder_;  //!< Helper to find objects.
};
}  // namespace HomoGebra
