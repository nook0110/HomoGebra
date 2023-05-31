#pragma once
#include "Observer.h"
#include "PlaneBody.h"
#include "PlaneImplementation.h"

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
class Plane final : public sf::Drawable
{
 public:
  /**
   * \brief Adds object to plane.
   *
   * \param construction Pointer to an object.
   */
  void AddConstruction(std::unique_ptr<Construction> construction);

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
   * \param event Event to update plane.
   */
  void Update(const sf::Event& event);

  /**
   * \brief Updates plane.
   *
   * \param target Render target to draw to.
   */
  void Update(sf::RenderTarget& target) const;

  /**
   * \brief Draws plane and all objects on it.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  /**
   * \brief Returns name generator.
   *
   * \return Name generator.
   */
  [[nodiscard]] const NameGenerator& GetNameGenerator() const;

 private:
  PlaneImplementation implementation_;  //!< Implementation of plane
  PlaneBody body_;                      //!< Body of plane
};