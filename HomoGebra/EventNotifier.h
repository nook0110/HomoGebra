#pragma once
#include <SFML/Window/Event.hpp>
#include <list>

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
   * \brief Process the event.
   *
   * \param event Event to process.
   */
  virtual void Update(const sf::Event& event) = 0;
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
   * \brief Notify all listeners of an event.
   *
   * \param event The event to notify.
   */
  void Notify(const sf::Event& event) const;

 private:
  std::list<EventListener*> listeners_;  //!< List of listeners.
};
