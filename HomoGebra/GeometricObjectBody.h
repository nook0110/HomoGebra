#pragma once

#include <SFML/Graphics.hpp>

#include "GeometricObjectImplementation.h"
#include "NameGenerator.h"

/**
 * \brief Name of object that you can draw.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class ObjectName final : public sf::Drawable, public sf::Transformable
{
 public:
  /**
   * \brief Constructs an object name.
   *
   * \param name Name of the object.
   */
  explicit ObjectName(std::string name = {});
  /**
   * \brief Destructor.
   *
   */
  ~ObjectName() override = default;

  /**
   * \brief Sets name of the object.
   *
   * \param name Name of the object.
   */
  void SetName(std::string name);
  /**
   * \brief Gets name of the object.
   *
   * \return Name of the object.
   */
  [[nodiscard]] const std::string& GetName() const;

  /**
   * \brief Draw the object name to a render target.
   *
   * \param target Render target to draw to.
   * \param states States of the render.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  inline static const std::string kFontPath =
      "Resources/font.ttf";                       //!< Path to font
  static constexpr unsigned kCharacterSize = 20;  //!< Character size
  inline static const sf::Color kTextColor =
      sf::Color::Black;  //!< Color of the text

  std::string name_;  //!< Name of the object

  sf::Font font_;  //!< Font of the text
  sf::Text text_;  //!< Text of the name
};

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
  void SetName(std::string name);

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

  void DrawArrow(sf::RenderTarget& target, sf::RenderStates states) const;

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

  ObjectName text_;  //!< Name of the name.
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
class LineBody : public sf::Drawable
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

  /**
   * \brief Draw line to a render target.
   *
   *
   *
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
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
class ConicBody : public sf::Drawable
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

  /**
   * \brief Updates the conic body.
   *
   * \param equation Equation of the conic.
   */
  void Update(const ConicEquation& equation);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  struct Equation
  {
    static constexpr std::array<Var, 2> kAnother = {Var::kY, Var::kX};

    using Solution = std::array<std::optional<Complex>, 2>;

    [[nodiscard]] Solution Solve(Var var, const Complex& another) const;

    std::array<Complex, 2> squares;
    Complex pair_product;
    std::array<Complex, 2> linears;
    Complex constant;
  };

  Equation equation_;
};