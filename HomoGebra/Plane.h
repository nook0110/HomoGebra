#pragma once
#include "PlaneBody.h"
#include "PlaneImplementation.h"

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
   * \param object Pointer to an object.
   */
  void AddObject(const std::shared_ptr<GeometricObject>& object);

  /**
   * \brief Returns objects of GeometricObjectType.
   *
   * \tparam GeometricObjectType Type of geometric object to get.
   *
   * \return Objects of GeometricObjectType.
   */
  template <class GeometricObjectType>
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetObjects()
      const;

  /**
   * \brief Returns all objects.
   *
   * \return All objects on plane.
   */
  [[nodiscard]] const std::vector<std::shared_ptr<GeometricObject>>&
  GetObjects() const;

  /**
   * \brief Returns all points.
   *
   * \return Points on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetPoints() const;

  /**
   * \brief Returns all lines.
   *
   * \return Lines on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetLines() const;

  /**
   * \brief Returns all conics.
   *
   * \return Conics on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetConics() const;

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

 private:
  PlaneImplementation implementation_;  //!< Implementation of plane
  PlaneBody body_;                      //!< Body of plane
};