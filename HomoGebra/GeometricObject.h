#pragma once

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"

/**
 * \brief Base class for geometric objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see Point
 * \see Line
 * \see Conic
 */
class GeometricObject : public sf::Drawable
{
 public:
  /**
   * \brief Default destructor.
   */
  ~GeometricObject() override = default;

  /**
   * \brief Destroy this object.
   *
   * \param plane Plane, where this object is located.
   */
  virtual void Destroy(Plane& plane) = 0;

  /**
   * \brief Update the body of the object.
   *
   * \param target Render target to draw to.
   */
  virtual void UpdateBody(sf::RenderTarget& target) = 0;

  /**
   * \brief Draw the point.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target,
            sf::RenderStates states) const override = 0;

 protected:
  /**
   * \brief Default constructor.
   */
  GeometricObject() = default;
};

/**
 * \brief Point on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PointBody
 * \see PointImplementation
 */
class Point final : public GeometricObject
{
 public:
  /**
   * \brief Construct point on a plane with equation.
   *
   * \param equation Equation of point.
   */
  explicit Point(const PointEquation& equation = PointEquation{});

  /**
   * \brief Default destructor.
   *
   */
  ~Point() override = default;

  /**
   * \brief Destroy this object.
   *
   * \param plane Plane, where this object is located.
   */
  void Destroy(Plane& plane) override;

  /**
   * \brief Set new equation of point.
   *
   * \param equation Equation of point
   */
  void SetEquation(const PointEquation& equation);

  /**
   * \brief Return current equation of point.
   *
   * \return Equation of point.
   */
  [[nodiscard]] const PointEquation& GetEquation() const;

  /**
   * \brief Update the body of the point.
   *
   * \param target Render target to draw to.
   */
  void UpdateBody(sf::RenderTarget& target) override;

  /**
   * \brief Draw the point.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /**
   * \brief Notify observers that this objected is destroyed.
   *
   * \param event Event of destruction.
   */
  void Notify(const Event::Destroyed& event) const;

  /**
   * \brief Calculates size of a body
   *
   * \detail Calculates size of pixel and than multiply size on a const
   *
   * \param target Render target to draw to.
   */
  static float CalculateSizeOfBody(const sf::RenderTarget& target);
  /*
   * Member data
   */
  PointBody body_;                      //!< Body, which you can draw.
  PointImplementation implementation_;  //!< Implementation.
};

/**
 * \brief Line on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see LineBody
 * \see LineImplementation
 */
class Line final : public GeometricObject
{
 public:
  /**
   * \brief Construct line on a plane with equation.
   *
   * \param equation Equation of line.
   */
  explicit Line(const LineEquation& equation = LineEquation{});

  /**
   * \brief Default destructor.
   */
  ~Line() override = default;

  /**
   * \brief Destroy this object.
   *
   * \param plane Plane, where this object is located.
   */
  void Destroy(Plane& plane) override;

  /**
   * \brief Set new equation of line.
   *
   * \param equation Equation of line.
   */
  void SetEquation(const LineEquation& equation);

  /**
   * \brief Return current equation of point.
   *
   * \return Equation of point.
   */
  [[nodiscard]] const LineEquation& GetEquation() const;

  /**
   * \brief Update the body of the line.
   *
   * \param target Render target to draw to.
   */
  void UpdateBody(sf::RenderTarget& target) override{};

  /**
   * \brief Draw the line.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /**
   * \brief Notify observers that this objected is destroyed
   *
   * \param event Event
   */
  void Notify(const Event::Destroyed& event) const;

  /*
   * Member data
   */
  LineBody body_;                      //!< Body, which you can draw.
  LineImplementation implementation_;  //!< Implementation.
};

/**
 * \brief Conic on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see ConicBody
 * \see ConicImplementation
 */
class Conic final : public GeometricObject
{
 public:
  /**
   * \brief Construct conic on a plane with equation.
   *
   * \param equation Equation of conic.
   */
  explicit Conic(const ConicEquation& equation = ConicEquation{});

  /**
   * \brief Destroy this object.
   *
   * \param plane Plane, where this object is located.
   */
  void Destroy(Plane& plane) final;

  /**
   * \brief Notify observers that this objected is destroyed
   *
   * \param event Event
   */
  void Notify(const Event::Destroyed& event) const;

  /**
   * \brief Update the body of the conic.
   *
   * \param target Render target to draw to.
   */
  void UpdateBody(sf::RenderTarget& target) override{};

  /**
   * \brief Draw the conic.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};