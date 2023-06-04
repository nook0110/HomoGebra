#pragma once
#include <list>
#include <memory>
#include <string>

class Plane;
class GeometricObject;

/**
 * \brief Events which can happen.
 */
namespace Event
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
struct Destroyed
{
  /*
   * Member data.
   */
  GeometricObject* object;  //!< Object which was destroyed.
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
}  // namespace Event

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
   * \brief Update the object, because sth moved.
   *
   * \param moved_event Tag with some information.
   *
   * \see Event::Moved
   */
  virtual void Update(const Event::Moved& moved_event) = 0;

  /**
   * \brief Update the object, because sth was destroyed.
   *
   * \param destroyed_event Tag with some information
   *
   * \see Event::Destroyed
   */
  virtual void Update(const Event::Destroyed& destroyed_event) = 0;

  /**
   * \brief Update the object, because sth was renamed.
   *
   * \param renamed_event Tag with some information
   *
   * \see Event::Renamed
   */
  virtual void Update(const Event::Renamed& renamed_event) = 0;
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
class ObservableGeometricObject
{
 public:
  /**
   * \brief Default destructor.
   */
  virtual ~ObservableGeometricObject() = default;

  /**
   * \brief Subscribe an observer on this object.
   *
   * \param observer Observer to add.
   */
  void Attach(GeometricObjectObserver* observer);

  /**
   * \brief Unsubscribe an observer on this object.
   *
   * \param observer Observer to delete.
   */
  void Detach(const GeometricObjectObserver* observer);

  /**
   * \brief Notify all subscribed observers that object was moved.
   *
   * \param moved_event Tag with some information.
   *
   * \see Event::Moved
   */
  void Notify(const Event::Moved& moved_event) const;

  /**
   * \brief Notify all subscribed observers that object was destroyed.
   *
   * \param destroyed Tag with some information (Plane where it was destroyed).
   *
   * \see Event:Destroyed
   */
  void Notify(const Event::Destroyed& destroyed) const;

  /**
   * \brief Notify all subscribed observers that object was renamed.
   *
   * \param renamed_event Tag with some information.
   *
   * \see Event::Renamed
   */
  void Notify(const Event::Renamed& renamed_event) const;

 private:
  /**
   * Member data.
   */
  std::list<GeometricObjectObserver*>
      observers_;  //!< List of subscribed observers.
};