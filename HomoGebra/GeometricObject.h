#pragma once

#include <SFML/Graphics.hpp>

#include "GeometricObjectBody.h"
#include "GeometricObjectImplementation.h"
#include "PlaneImplementation.h"

namespace HomoGebra
{
/**
 * \brief Base class for geometric objects.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 *
 * \see Point
 * \see Line
 * \see Conic
 */
class GeometricObject : public sf::Drawable,
                        public ObservableInterface<GeometricObjectObserver>
{
 public:
  /**
   * \brief Default destructor.
   */
  ~GeometricObject() override = default;

  /**
   * \brief Destroy this object.
   *
   */
  virtual void AlertDestruction() const = 0;

  /**
   * \brief Update the body of the object.
   *
   * \param target Render target to draw to.
   */
  virtual void UpdateBody(const sf::RenderTarget& target) = 0;

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
  virtual void SetName(std::string name) = 0;

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
  [[nodiscard]] virtual Distance GetDistance(
      const sf::Vector2f& position) const = 0;

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
 * \version 1.0
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
  explicit Point(PointEquation equation = PointEquation{});

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
   */
  void AlertDestruction() const override;

  /**
   * \brief Set new equation of point.
   *
   * \param equation Equation of point
   */
  void SetEquation(PointEquation equation);

  /**
   * \brief Return current equation of point.
   *
   * \return Equation of point.
   */
  [[nodiscard]] const PointEquation& GetEquation() const;

  [[nodiscard]] Distance GetDistance(
      const sf::Vector2f& position) const override;

  void Attach(GeometricObjectObserver* observer) override;

  void Detach(const GeometricObjectObserver* observer) override;
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
  void UpdateBody(const sf::RenderTarget& target) override;

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
  void SetName(std::string name) override;

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override;

  ///@}
 private:
  /**
   * \brief Notify observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify.
   */
  template <class Event>
  void Notify(const Event& event) const;

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
 * \version 1.0
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
  explicit Line(LineEquation equation = LineEquation{});

  /**
   * \brief Default destructor.
   */
  ~Line() override = default;

  /**
   * \brief Destroy this object.
   *
   */
  void AlertDestruction() const override;

  /**
   * \brief Set new equation of line.
   *
   * \param equation Equation of line.
   */
  void SetEquation(LineEquation equation);

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
  void UpdateBody(const sf::RenderTarget& target) override;

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
  void SetName(std::string name) override;

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override;

  /**
   * \brief Attaches observer to this object.
   *
   * \param observer Observer to attach.
   */
  void Attach(GeometricObjectObserver* observer) override;

  void Detach(const GeometricObjectObserver* observer) override;

  [[nodiscard]] Distance GetDistance(
      const sf::Vector2f& position) const override;

 private:
  /**
   * \brief Notify observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify.
   */
  template <class Event>
  void Notify(const Event& event) const;

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
 * \version 1.0
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
  explicit Conic(ConicEquation equation = ConicEquation{});

  /**
   * \brief Destroy this object.
   *
   */
  void AlertDestruction() const override;

  /**
   * \brief Set new equation of conic.
   *
   * \param equation Equation of conic.
   */
  void SetEquation(ConicEquation equation);

  /**
   * \brief Update the body of the conic.
   *
   * \param target Render target to draw to.
   */
  void UpdateBody(const sf::RenderTarget& target) override;

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
  void SetName(std::string name) override;

  /**
   * \brief Gets name of object.
   *
   * \return Name of object.
   */
  [[nodiscard]] const std::string& GetName() const override;

  /**
   * \brief Attaches observer to this object.
   *
   * \param observer Observer to attach.
   */
  void Attach(GeometricObjectObserver* observer) override;

  void Detach(const GeometricObjectObserver* observer) override;

  [[nodiscard]] Distance GetDistance(
      const sf::Vector2f& position) const override;

 private:
  /**
   * \brief Notify observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify.
   */
  template <class Event>
  void Notify(const Event& event) const;

  /*
   * Member data
   */
  ConicBody body_;                      //!< Body, which you can draw.
  ConicImplementation implementation_;  //!< Implementation.
};
}  // namespace HomoGebra