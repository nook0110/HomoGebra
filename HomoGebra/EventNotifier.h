#pragma once
#include <SFML/Window/Event.hpp>
#include <list>

class EventListener
{
 public:
  virtual void Update(const sf::Event& event) = 0;
};

class EventNotifier
{
  void Attach(EventListener* observer);

  void Detach(const EventListener* observer);

  void Notify(const sf::Event& event) const;

 private:
  std::list<EventListener*> listeners_;
};
