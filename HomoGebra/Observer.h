#pragma once
#include <list>
#include <string>

namespace HomoGebra
{
class Plane;
class GeometricObject;

/**
 * \brief Interface for observers of geometric objects.
 *
 * \author nook0110
 */
template <class Observer>
class ObservableInterface
{
 public:
  /**
   * \brief Default destructor.
   */
  virtual ~ObservableInterface() = default;

  /**
   * \brief Subscribe an observer on this object.
   *
   * \param observer Observer to add.
   */
  virtual void Attach(Observer* observer) = 0;

  /**
   * \brief Unsubscribe an observer on this object.
   *
   * \param observer Observer to delete.
   */
  virtual void Detach(const Observer* observer) = 0;
};

template <class Observer>
class Observable : public ObservableInterface<Observer>
{
 public:
  /**
   * \brief Default destructor.
   */
  ~Observable() override = default;

  /**
   * \brief Subscribe an observer on this object.
   *
   * \param observer Observer to add.
   */
  void Attach(Observer* observer) override;

  /**
   * \brief Unsubscribe an observer on this object.
   *
   * \param observer Observer to delete.
   */
  void Detach(const Observer* observer) override;

  /**
   * \brief Notify all observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify about.
   */
  template <class Event>
  void Notify(const Event& event) const;

 private:
  /**
   * Member data.
   */
  std::list<Observer*> observers_;  //!< List of subscribed observers.
};

/**
 * \brief Events which can happen with objects.
 */
namespace ObjectEvent
{
/**
 * \brief Tag that shows that object was moved.
 */
struct Moved
{
  GeometricObject* object;  //!< Object which was moved.
};

/**
 * \brief Tag that shows that object was destroyed.
 */
struct GoingToBeDestroyed
{
  /*
   * Member data.
   */
  const GeometricObject* object;  //!< Object which was destroyed.
};

/**
 * \brief Tag that shows that objects was renamed.
 */
struct Renamed
{
  /*
   *    Member data.
   */
  GeometricObject* object;  //!< Object which was renamed.
  std::string old_name;     //!< Old name of object.
  std::string new_name;     //!< New name of object.
};
}  // namespace ObjectEvent

/**
 * \brief Makes Construction an observer.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Implements pattern called 'Observer'.
 *
 * \see ObservableGeometricObject
 * \see Construction
 */
class GeometricObjectObserver
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  GeometricObjectObserver() = default;

  /**
   * \brief Default destructor.
   */
  virtual ~GeometricObjectObserver() = default;

  /**
   * \brief Update, because sth moved.
   *
   * \param moved_event Tag with some information.
   *
   * \see ObjectEvent::Moved
   */
  virtual void Update(const ObjectEvent::Moved& moved_event) = 0;

  /**
   * \brief Update, because sth was destroyed.
   *
   * \param destroyed_event Tag with some information
   *
   * \see ObjectEvent::Destroyed
   */
  virtual void Update(
      const ObjectEvent::GoingToBeDestroyed& destroyed_event) = 0;

  /**
   * \brief Update, because sth was renamed.
   *
   * \param renamed_event Tag with some information
   *
   * \see ObjectEvent::Renamed
   */
  virtual void Update(const ObjectEvent::Renamed& renamed_event) = 0;
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
 * \details Implements pattern called 'Observer'.
 *
 * \see ConstructionObserver
 * \see GeometricObjectImplementation
 */
class ObservableGeometricObject : public Observable<GeometricObjectObserver>
{
 public:
  /**
   * \brief Default destructor.
   */
  ~ObservableGeometricObject() override = default;

  /**
   * \brief Notify all observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify about.
   */
  template <class Event>
  void Notify(const Event& event) const;
};

namespace PlaneEvent
{
/**
 * \brief Tag that shows that object was removed.
 *
 * \author nook0110
 */
struct ObjectRemoved
{
  const GeometricObject* removed_object{};
};
}  // namespace PlaneEvent

class PlaneObserver
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  PlaneObserver() = default;

  /**
   * \brief Default destructor.
   */
  virtual ~PlaneObserver() = default;

  /**
   * \brief Update, because sth was destroyed.
   *
   * \param object_removed Tag with some information
   *
   * \see ObjectEvent::Destroyed
   */
  virtual void Update(const PlaneEvent::ObjectRemoved& object_removed) = 0;
};

class ObservablePlane : public Observable<PlaneObserver>
{
 public:
  /**
   * \brief Default destructor.
   */
  ~ObservablePlane() override = default;

  /**
   * \brief Notify all observers about event.
   *
   * \tparam Event Type of event.
   * \param event Event to notify about.
   */
  template <class Event>
  void Notify(const Event& event) const;
};

template Observable<GeometricObjectObserver>;
template Observable<PlaneObserver>;
}  // namespace HomoGebra