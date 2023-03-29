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
   * \brief Add object to plane.
   *
   * \param object Pointer to an object.
   */
  void AddObject(const std::shared_ptr<GeometricObject>& object);

  /**
   * \brief Get all objects.
   *
   * \return All objects on plane.
   */
  [[nodiscard]] const std::vector<std::shared_ptr<GeometricObject>>&
  GetObjects() const;

  /**
   * \brief Get all points.
   *
   * \return Points on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetPoints() const;

  /**
   * \brief Get all lines.
   *
   * \return Lines on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetLines() const;

  /**
   * \brief Get all conics.
   *
   * \return Conics on a plane.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetConics() const;

  void Update(sf::RenderTarget& target);

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
