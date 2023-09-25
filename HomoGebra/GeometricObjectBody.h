#pragma once

#include <SFML/Graphics.hpp>

#include "DistanceUtilities.h"
#include "GeometricObjectImplementation.h"
#include "NameGenerator.h"

/**
 * \brief Name of object that you can draw.
 *
 * \author nook0110
 *
 * \version 1.0
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
   * \brief Sets size of the object name.
   *
   * \param size Size of the object name.
   */
  void SetSize(float size);
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
  static constexpr unsigned kCharacterSize = 50;  //!< Character size
  inline static const sf::Color kTextColor =
      sf::Color{0, 0, 0};  //!< Color of the text

  std::string name_;  //!< Name of the object

  sf::Font font_;  //!< Font of the text
  sf::Text text_;  //!< Text of the name
};

/**
 * \brief Base class for bodies.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class ObjectBody : public sf::Drawable
{
 public:
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
   * \brief Sets position of the name.
   *
   * \param position Position of the name.
   */
  void SetNamePosition(const sf::Vector2f& position);

  /**
   * \brief Sets size of the name.
   *
   * \param size Size of the name.
   */
  void SetNameSize(float size);

  /**
   * \brief Draw the object body to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  /**
   * \brief Gets distance from object to position.
   *
   * \param position Position to calculate distance.
   *
   * \return Distance from object to position.
   */
  [[nodiscard]] virtual Distance GetDistance(
      const sf::Vector2f& position) const = 0;

 private:
  ObjectName text_;  //!< Name of the name.
};

/**
 * \brief Body of a point
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 */
class PointBody final : public ObjectBody
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
  void Update(const PointEquation& equation, float size = 0);

  /**
   * \brief Draw the point to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  /**
   * \brief Draw arrow to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void DrawArrow(sf::RenderTarget& target, sf::RenderStates states) const;

  Distance GetDistance(const sf::Vector2f& position) const override;

 private:
  /**
   * Member data.
   */

  /**
   * \brief Projective position of the point.
   *
   * \author nook0110
   *
   * \version 1.0
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
 * \version 1.0
 *
 * \date February 2023
 */
class LineBody final : public ObjectBody
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
  ~LineBody() override = default;

  /**
   * \brief Updates the line body.
   *
   * \param equation Equation of the line.
   */
  void Update(const LineEquation& equation);

  /**
   * \brief Draw line to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Distance GetDistance(const sf::Vector2f& position) const override;

 private:
  /**
   * \brief Equation of a line.
   *
   * \author nook0110
   *
   * \version 1.0
   *
   * \date July 2023
   */
  struct Equation
  {
    /*
     * Line equation:
     * a*x + b*y + c = 0
     */
    float a;  //!< Coefficient of x.
    float b;  //!< Coefficient of y.
    float c;  //!< Constant.

    /**
     * \brief Solve the equation for a variable.
     *
     * \param var Variable to solve for.
     * \param another Another variable value.
     *
     * \return Value of the variable.
     */
    [[nodiscard]] float Solve(Var var, float another) const;
  };

  std::optional<Equation> equation_;  //!< Equation of the line.
};

/**
 * \brief Body of a conic.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 */
class ConicBody : public ObjectBody
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
  ~ConicBody() override = default;

  /**
   * \brief Updates the conic body.
   *
   * \param equation Equation of the conic.
   */
  void Update(const ConicEquation& equation);

  /**
   * \brief Draw conic to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Distance GetDistance(const sf::Vector2f& position) const override;

 private:
  /**
   * \brief Equation of a conic that lies on a real plane.
   *
   */
  struct Equation
  {
    static constexpr std::array<Var, 2> kAnother = {
        Var::kY, Var::kX};  //!< Another variable of each variable.

    using Solution = std::array<std::optional<Complex>,
                                2>;  //!< Solution of the equation.

    /**
     * \brief Solves the equation for variable.
     *
     * \param var Variable to solve for.
     * \param another Another variable value.
     *
     * \return Solution of the equation.
     */
    [[nodiscard]] Solution Solve(Var var, const Complex& another) const;

    std::array<long double, 2>
        squares;               //!< Coefficient of the squares of the variables.
    long double pair_product;  //!< Coefficient of the product of the variables.
    std::array<long double, 2> linears;  //!< Coefficient of the variables.
    long double constant;                //!< Constant coefficient.
  };

  std::optional<Equation> equation_;  //!< Equation of the conic.
};
