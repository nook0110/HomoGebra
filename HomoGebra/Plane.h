#pragma once
#include <SFML/Graphics.hpp>

#include "EventNotifier.h"
#include "Observer.h"
#include "PlaneImplementation.h"

namespace HomoGebra
{
class Construction;

/**
 * \brief Container for all objects, which you can draw.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PlaneImplementation
 * \see PlaneBody
 */
class Plane final : public sf::Drawable,
                    public ObservableInterface<PlaneObserver>,
                    public EventListener,
                    public EventNotifier
{
 public:
  using EventNotifier::Attach;
  using EventNotifier::Detach;

  /**
   * \brief Adds object to plane.
   *
   * \param construction Pointer to an object.
   */
  void AddConstruction(std::unique_ptr<Construction> construction);

  /**
   * \brief Deletes object from plane.
   *
   * \param construction Pointer to an object.
   */
  void DeleteConstruction(Construction* construction);

  /**
   * \brief Deletes object from plane.
   *
   * \param object Pointer to an object.
   */
  void DeleteObject(const GeometricObject* object);

  /**
   * \brief Returns objects of GeometricObjectType.
   *
   * \tparam GeometricObjectType Type of geometric object to get.
   *
   * \return Objects of GeometricObjectType.
   */
  template <class GeometricObjectType>
  [[nodiscard]] std::vector<GeometricObject*> GetObjects() const;

  /**
   * \brief Updates plane.
   *
   * \param target Render target to draw to.
   */
  void UpdateBodies(const sf::RenderTarget& target) const;

  /**
   * \brief Returns name generator.
   *
   * \return Name generator.
   */
  [[nodiscard]] const NameGenerator& GetNameGenerator() const;

  void Attach(PlaneObserver* observer) override;

  void Detach(const PlaneObserver* observer) override;

 private:
  /**
   * \brief Draws plane and all objects on it.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Update(const UserEvent::Click& clicked_event) override;

  PlaneImplementation implementation_;  //!< Implementation of plane
};
}  // namespace HomoGebra