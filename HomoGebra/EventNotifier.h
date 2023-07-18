#pragma once
#include <SFML/System/Vector2.hpp>
#include <list>

namespace UserEvent
{
/**
 * \brief Tag that shows that user clicked on the screen.
 */
struct Click
{
  sf::Vector2f position;  //!< Position of the click.
};

struct Unclick
{
  sf::Vector2f position;  //!< Position of the unclick.
};
}  // namespace UserEvent

/**
 * \brief Class that listens to notifier.
 *
 * \see EventNotifier
 *
 * \author nook0110
 */
class EventListener
{
 public:
  /**
   * \brief Default destructor.
   *
   */
  virtual ~EventListener() = default;

  /**
   * \brief Update, because user clicked.
   *
   * \param clicked_event Tag with some information
   *
   * \see UserEvent::clicked_event
   */
  virtual void Update(const UserEvent::Click& clicked_event) = 0;
};

/**
 * \brief Class that listens to events and notifies listens.
 *
 * \author nook0110
 */
class EventNotifier
{
 public:
  /**
   * \brief Attach a listener to the notifier.
   *
   * \param listener The listener to attach.
   */
  void Attach(EventListener* listener);

  /**
   * \brief Detach a listener from the notifier.
   *
   * \param listener The listener to detach.
   */
  void Detach(const EventListener* listener);

  /**
   * \brief Notify all listeners.
   *
   * \tparam Event Type of event.
   * \param event Event to notify about.
   */
  template <class Event>
  void Notify(const Event& event) const;

 private:
  std::list<EventListener*> listeners_;  //!< List of listeners.
};
