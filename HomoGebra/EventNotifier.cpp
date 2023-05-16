#include "EventNotifier.h"

void EventNotifier::Attach(EventListener* listener)
{
  // Add listener to list
  listeners_.push_back(listener);
}

void EventNotifier::Detach(const EventListener* listener)
{
  // Remove listener from list
  listeners_.remove_if([listener](const EventListener* obs)
                       { return obs == listener; });
}

void EventNotifier::Notify(const sf::Event& event) const
{
  // Update all listeners
  for (const auto& listener : listeners_) listener->Update(event);
}