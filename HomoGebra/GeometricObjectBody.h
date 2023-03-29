#pragma once

#include <SFML/Graphics.hpp>

#include "GeometricObjectImplementation.h"

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

  void Update(const PointEquation& equation, const float size = 0);

  void draw(sf::RenderTarget& target, sf::RenderStates) const override;

 private:
  /**
   * Member data.
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