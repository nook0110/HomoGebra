#pragma once

#include <SFML/Graphics.hpp>

class GeometricObjectBody : public sf::Drawable
{
public:
  ~GeometricObjectBody() override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
private:
  GeometricObjectBody() = default;
};

class PointBody : public GeometricObjectBody
{
public:
  ~PointBody() override = default;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
private:
  PointBody();
};

class LineBody : public GeometricObjectBody
{
public:
  ~LineBody() override = default;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
private:
  LineBody();
};

class ConicBody : public GeometricObjectBody
{
public:
  ~ConicBody() override = default;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
private:
  ConicBody();
};