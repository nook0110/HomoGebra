#pragma once
#include <list>

#include "Equation.h"

/**
* \brief Events which can happen
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
  struct Destroyed {};
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
 * \detail Implements pattern called 'Observer'
 *
 * \see ObservableGeometricObject
 * \see Construction
 *
*/
class ConstructionObserver
{
public:
  virtual ~ConstructionObserver() = default;

  virtual void Update(Event::Moved) const = 0;
  virtual void Update(Event::Destroyed) const = 0;

private:
  std::list<const ConstructionObserver*> observers_; //!< List of subscribed observers
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
 * \detail Implements pattern called 'Observer'
 *
 * \see ConstructionObserver
 * \see GeometricObjectImplementation
*/
class ObservableGeometricObject
{
public:

  virtual ~ObservableGeometricObject() = default;

  /**
   * \brief Subscribe an observer on this object
   *
   * \param observer Observer to add
   */
  void Attach(std::shared_ptr<const ConstructionObserver> observer);

  /**
   * \brief Unsubscribe an observer on this object
   *
   * \param observer Observer to delete
   */
  void Detach(const ConstructionObserver* observer);

protected:
  /**
  * \brief Notify all subscribed observers that object was moved
  *
  */
  void Notify(Event::Moved) const;

  /**
  * \brief Notify all subscribed observers that object was destroyed
  *
  */
  void Notify(Event::Destroyed) const;

private:
  /**
   * Member data.
   */
  std::list<std::shared_ptr<const ConstructionObserver>> observers_; //!< List of subscribed observers
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
   * \brief Sets new equation of point.
   *
   * \param equation Equation of point
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
   * \brief Default constructor.
   *
   */
  PointImplementation();

  /**
   * Member data.
   */
  PointEquation equation_; //!< Point equation
};

class LineImplementation : public GeometricObjectImplementation
{
public:
  /**
   * \brief Sets new equation of line.
   *
   * \param equation Equation of line
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
   * \brief Default constructor.
   *
   */
  LineImplementation();

  /**
   * Member data.
   */
  LineEquation equation_; //!< Line equation
};

class ConicImplementation : public GeometricObjectImplementation
{
public:
  /**
   * \brief Sets new equation of conic.
   *
   * \param equation Equation of conic
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
   * \brief Default constructor.
   *
   */
  ConicImplementation();

  /**
   * Member data.
   */
  ConicEquation equation_; //!< Conic equation
};

/**
 * \brief Defines how object is created.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Updates positions of objects
 * \see GeometricObjectImplementation
*/
class Construction : public ConstructionObserver
{
public:
  /**
   * \brief Constructor deleted.
   * 
   */
  Construction() = delete;

  /**
   * \brief Default destructor.
   * 
   */
  ~Construction() override = default;
};

/**
 * \brief Defines how point is created.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Updates position of point
*/
class ConstructionPoint : public Construction
{
public:
  /**
   * \brief Constructor deleted.
   * 
   */
  ConstructionPoint() = delete;

  /**
  * \brief Default destructor.
  * 
  */
  ~ConstructionPoint() override = default;

  /**
   * Recalculate equation of point.
   * 
   * \return New equation of point.
   */
  virtual PointEquation RecalculateEquation() const = 0;

  /**
   * \brief Update the object because sth moved.
   * 
   * \param Tag for tag dispatch
   */
  void Update(Event::Moved) const override;
protected:
  PointImplementation& object_;
private:
};

/**
 * \brief Construction of a casual point on a plane.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Have no dependence on other objects
*/
class ConstructionOnPlane : public ConstructionPoint
{
public:
  ~ConstructionOnPlane() override = default;
};

class ConstructionFromTwoLines : public ConstructionPoint
{
};

class ConstructionLine : public Construction
{
public:
  /**
   * \brief Constructor deleted.
   */
  ConstructionLine() = delete;

  /**
   * \brief Default destructor.
   */
  ~ConstructionLine() override = default;

  /**
   * Recalculate equation of point.
   *
   * \return New equation of point.
   */
  virtual LineEquation RecalculateEquation() const = 0;

  /**
   * \brief Update object because sth moved.
   * 
   * \param Tag for tag dispatch 
   */
  void Update(Event::Moved) const override;
private:
  LineImplementation& object_;
};

class ConstructionConic : public Construction
{};