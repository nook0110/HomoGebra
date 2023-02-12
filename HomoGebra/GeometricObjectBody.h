#pragma once

#include <SFML/Graphics.hpp>

class GeometricObjectBody : public sf::Drawable
{
public:
  /**
   * \brief Destructor.
   *
   */
  ~GeometricObjectBody() override;

private:
  /**
   * \brief Draw the object to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

  /**
   * \brief Default constructor.
   *
   */
  GeometricObjectBody() = default;
};

class PointBody : public GeometricObjectBody
{
public:
  /**
   * \brief Destructor.
   *
   */
  ~PointBody() override = default;

private:
  /**
   * \brief Draw the point to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

  /**
   * \brief Default constructor.
   *
   */
  PointBody();
};

class LineBody : public GeometricObjectBody
{
public:
  /**
   * \brief Destructor.
   *
   */
  ~LineBody() override = default;

private:
  /**
   * \brief Draw the line to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

  /**
   * \brief Default constructor.
   *
   */
  LineBody();
};

class ConicBody : public GeometricObjectBody
{
public:
  /**
   * \brief Destructor.
   *
   */
  ~ConicBody() override = default;

private:
  /**
   * \brief Draw the conic to a render target.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

  /**
   * \brief Default constructor.
   *
   */
  ConicBody();
};