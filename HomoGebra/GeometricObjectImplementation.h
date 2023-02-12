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
 * \see GeometricObject
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
private:
  /**
   * \brief Default constructor.
   *
   */
  PointImplementation();

  /**
   * Member data.
   */
};

class LineImplementation : public GeometricObjectImplementation
{};

class ConicImplementation : public GeometricObjectImplementation
{};

/**
 * \brief Class that manages dependencies between objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details After notified, updates positions of objects
 * \see GeometricObjectImplementation
*/
class Construction : public ConstructionObserver
{};

class ConstructionPoint : public Construction
{};

class ConstructionOnPlane : public ConstructionPoint
{
public:
  void Update(Event::Destroyed) const override;
};

class ConstructionLine : public Construction
{};

class ConstructionConic : public Construction
{};