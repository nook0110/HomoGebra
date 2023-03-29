#include "Creation.h"

PointCreator::PointCreator(Plane& plane, sf::RenderWindow& window)
    : window_(window), factory_(plane)
{
  InitActionMap();
}

void PointCreator::Update(const sf::Event& event)
{
  // Update the action map.
  action_map_.pushEvent(event);

  // Check if mouse was clicked
  if (action_map_.isActive(Action::kCreatePoint))
  {
    CreatePoint();
  }

  // Clear last event
  action_map_.clearEvents();
}

void PointCreator::InitActionMap()
{
  // Create the action map.
  action_map_[Action::kCreatePoint] =
      thor::Action(sf::Mouse::Left, thor::Action::ReleaseOnce);
}

void PointCreator::CreatePoint()
{
  // Get coordinates of a mouse
  const auto mouse_position = sf::Mouse::getPosition(window_);

  // Convert mouse coordinates to world coordinates.
  const auto point_position = window_.mapPixelToCoords(mouse_position);

  // Create point equation
  const PointEquation point_equation(HomogeneousCoordinate{point_position});

  // Create a point.
  factory_.OnPlane(point_equation);
}

CreationDirector::CreationDirector(std::unique_ptr<Creator>&& creator)
    : creator_(std::move(creator))
{}

void CreationDirector::Update(const sf::Event& event) const
{
  if (creator_)
  {
    creator_->Update(event);
  }
}