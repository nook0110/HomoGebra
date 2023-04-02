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
   * \brief Set name of the point.
   *
   * \param name Name of the point.
   */
  void SetName(const std::string& name);

  /**
   * \brief Gets name of the point.
   *
   * \return Name of the point.
   */
  [[nodiscard]] const std::string& GetName() const;

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

  std::string name_;  //!< Name of the point.
  sf::Text text_;     //!< Text of the name.

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
    sf::Vector2f position;  //!< Position of the point.

    bool is_at_infinity = false;  //!< Is the point at infinity?
  };

  /**
   * \brief Calculates the projective position of the point.
   *
   * \param equation Equation of the point.
   *
   * \return Projective position of the point.
   */
  static std::optional<ProjectivePosition> CalculatePosition(
      const PointEquation& equation);

  std::optional<ProjectivePosition>
      position_;          //!< Projective position of the point.
  sf::CircleShape body_;  //!< Body of the point.
};

/**
 * \brief Body of a line.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
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

/**
 * \brief Body of a conic.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
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