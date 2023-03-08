#pragma once
#include <list>

#include "Equation.h"

class Plane;

/**
* \brief Events which can happen.
*
*/
namespace Event
{
  /**
   * \brief Tag that shows that object was moved.
   */
  struct Moved {};

  /**
   * \brief Tag that shows that object was destroyed.
   */
  struct Destroyed
  {
    /*
    * Member data.
    */
    Plane& plane_; //!< Plane where object was destroyed.
  };
}

/**
 * \brief Makes Construction an observer.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \detail Implements pattern called 'Observer'.
 *
 * \see ObservableGeometricObject
 * \see Construction
*/
class ConstructionObserver
{
public:
  /**
  * Default destructor.
  */
  virtual ~ConstructionObserver() = default;

  /**
  * \brief Update the object, because sth moved.
  *
  * \param Tag with some information.
  */
  virtual void Update(const Event::Moved&) = 0;

  /**
  * \brief Update the object, because sth was destroyed.
  *
  * \param Tag with some information (Plane where it was destroyed).
  */
  virtual void Update(const Event::Destroyed&) = 0;
private:
  std::list<const ConstructionObserver*> observers_; //!< List of subscribed observers.
};

/**
 * \brief Makes GeometricObjectImplementation observable.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \detail Implements pattern called 'Observer'.
 *
 * \see ConstructionObserver
 * \see GeometricObjectImplementation
*/
class ObservableGeometricObject
{
public:

  virtual ~ObservableGeometricObject() = default;

  /**
   * \brief Subscribe an observer on this object.
   *
   * \param observer Observer to add.
   */
  void Attach(const std::shared_ptr<ConstructionObserver>& observer);

  /**
   * \brief Unsubscribe an observer on this object.
   *
   * \param observer Observer to delete.
   */
  void Detach(const ConstructionObserver* observer);

protected:
  /**
  * \brief Notify all subscribed observers that object was moved.
  *
  */
  void Notify(const Event::Moved&) const;

  /**
  * \brief Notify all subscribed observers that object was destroyed.
  *
  */
  void Notify(const Event::Destroyed&) const;

private:
  /**
   * Member data.
   */
  std::list<std::shared_ptr<ConstructionObserver>> observers_; //!< List of subscribed observers.
};

/**
 * \brief Base class for implementations of geometric objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \see PointImplementation
 * \see LineImplementation
 * \see ConicImplementation
 *
*/
class GeometricObjectImplementation : public ObservableGeometricObject
{
public:
  /**
  * \brief Destructor.
  *
  */
  ~GeometricObjectImplementation() override;
};

class PointImplementation : public GeometricObjectImplementation
{
public:
  /**
 * \brief Default constructor.
 *
 */
  PointImplementation() = default;

  /**
   * \brief Sets new equation of point.
   *
   * \param equation Equation of point.
  */
  void SetEquation(const PointEquation& equation);

  /**
   * \brief Return current equation of point.
   *
   * \return Point equation.
   */
  const PointEquation& GetEquation() const;

private:

  /**
   * Member data.
   */
  PointEquation equation_; //!< Point equation.
};

class LineImplementation : public GeometricObjectImplementation
{
public:
  /**
 * \brief Default constructor.
 *
 */
  LineImplementation() = default;

  /**
   * \brief Sets new equation of line.
   *
   * \param equation Equation of line.
  */
  void SetEquation(const LineEquation& equation);

  /**
   * \brief Return equation of line.
   *
   * \return Line equation.
   */
  const LineEquation& GetEquation() const;

private:

  /**
   * Member data.
   */
  LineEquation equation_; //!< Line equation.
};

class ConicImplementation : public GeometricObjectImplementation
{
public:
  /**
 * \brief Default constructor.
 *
 */
  ConicImplementation() = default;

  /**
   * \brief Sets new equation of conic.
   *
   * \param equation Equation of conic.
  */
  void SetEquation(const ConicEquation& equation);

  /**
   * \brief Return equation of conic.
   *
   * \return Conic equation.
   */
  const ConicEquation& GetEquation() const;

private:

  /**
   * Member data.
   */
  ConicEquation equation_; //!< Conic equation.
};
