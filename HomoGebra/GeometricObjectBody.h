#pragma once

#include <SFML/Graphics.hpp>

#include "GeometricObjectImplementation.h"

/**
 * \brief Body of a point
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class PointBody final : public sf::Drawable
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  PointBody();

  /**
   * \brief Destructor.
   *
   */
  ~PointBody() override = default;

  /**
   * \brief Updates the point body.
   *
   * \param equation Equation of the point.
   * \param size Size of the point.
   */
  void Update(const PointEquation& equation, const float size = 0);

  /**
   * \brief Draw the point to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /**
   * Member data.
   */

  /**
   * \brief Projective position of the point.
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date February 2023
   */
  struct ProjectivePosition
  {
    sf::Vector2f position;

    bool is_at_infinity = false;
  };

  static std::optional<ProjectivePosition> CalculatePosition(
      const PointEquation& equation);

  std::optional<ProjectivePosition> position_;
  sf::CircleShape body_;
};

class LineBody
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  LineBody() = default;

  /**
   * \brief Destructor.
   *
   */
  ~LineBody() = default;
};

class ConicBody
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  ConicBody() = default;

  /**
   * \brief Destructor.
   *
   */
  ~ConicBody() = default;
};