#pragma once

#include <SFML/Graphics.hpp>

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"
#include "PlaneImplementation.h"

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

  /**
   * \brief Sets new name of object.
   *
   * \param name New name of object.
   */
  virtual void SetName(const std::string& name) = 0;

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] virtual const std::string& GetName() const = 0;

  /**
   * \brief Gets distance from object to position.
   *
   * \param position Position to calculate distance.
   *
   * \return Distance from object to position.
   */
  [[nodiscard]] virtual float GetDistance(sf::Vector2f position) const
  {
    return 0;
  }

  /**
   * \brief Attaches observer to this object.
   *
   * \param observer Observer to attach.
   */
  virtual void Attach(GeometricObjectObserver* observer) = 0;

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
   *  \brief Implementation interface.
   */
  ///@{
  /* */

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

  void Attach(GeometricObjectObserver* observer) override;

  ///@}

  /**
   *  \brief Body interface.
   */
  ///@{
  /* */

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

  /**
   * \brief Sets new name of object.
   *
   * \param name New name of object.
   */
  void SetName(const std::string& name) override;

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override;

  ///@}
 private:
  /**
   * \brief Notify observers that this objected was destroyed.
   *
   * \param event Event of destruction.
   */
  void Notify(const Event::Destroyed& event) const;

  /**
   * \brief Notify observers that this objected was renamed.
   *
   * \param event Event of renaming.
   */
  void Notify(const Event::Renamed& event) const;

  /**
   * \brief Calculates size of a body
   *
   * \details Calculates size of pixel and than multiply size on a const
   *
   * \param target Render target to draw to.
   *
   * \return Size of body.
   */
  static float CalculateSizeOfBody(const sf::RenderTarget& target);
  /*
   * Member data
   */
  PointBody body_;                      //!< Body, which you can draw.
  PointImplementation implementation_;  //!< Implementation.
};

class LineImplementation;
class LineBody;

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

  /**
   * \brief Sets new name of object.
   *
   * \param name New name of object.
   */
  void SetName(const std::string& name) override{};

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override { return {}; };

  /**
   * \brief Attaches observer to this object.
   *
   * \param observer Observer to attach.
   */
  void Attach(GeometricObjectObserver* observer) override {}

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

class ConicImplementation;
class ConicBody;

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
  void Destroy(Plane& plane) override;

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
  void UpdateBody(sf::RenderTarget& target) override;

  /**
   * \brief Draw the conic.
   *
   * \param target Render target to draw to.
   * \param states Current render states.
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  /**
   * \brief Sets new name of object.
   *
   * \param name New name of object.
   */
  void SetName(const std::string& name) override{};

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override { return {}; }

  /**
   * \brief Attaches observer to this object.
   *
   * \param observer Observer to attach.
   */
  void Attach(GeometricObjectObserver* observer) override {}

 private:
  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};