#pragma once
#include <SFML/Graphics.hpp>

#include "NameGenerator.h"

/**
 * \brief Class that represents a plane body.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class PlaneBody final : public sf::Drawable
{
 public:
  /**
   * \brief Draw the plane to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  /**
   * \brief Update the plane body.
   *
   * \param event Event to update the plane body.
   */
  void Update(const sf::Event& event);

  /**
   * \brief Get the view of the plane.
   *
   * \return View of the plane.
   */
  const sf::View& GetView() const;

 private:
  /**
   * \brief Update the plane body with mouse event.
   *
   * \param event Mouse event to update the plane body.
   */
  void MouseEventUpdate(const sf::Event& event);

  sf::View view_;  //!< View of the plane.
};
