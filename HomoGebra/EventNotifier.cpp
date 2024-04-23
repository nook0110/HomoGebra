#include "EventNotifier.h"

#include <algorithm>

namespace HomoGebra
{
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

template <class Event>
void EventNotifier::Notify(const Event& event) const
{
  // Update all listeners
  std::ranges::for_each(
      listeners_, [&event](const auto& listener) { listener->Update(event); });
}

template void EventNotifier::Notify<UserEvent::Click>(
    const UserEvent::Click& event) const;
}  // namespace HomoGebra