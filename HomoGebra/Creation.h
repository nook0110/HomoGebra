#pragma once
#include <Thor/Input.hpp>

#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "Plane.h"

class Creator
{
 public:
  virtual ~Creator() = default;

  virtual void Update(const sf::Event& event) = 0;
};

class PointCreator final : public Creator
{
 public:
  PointCreator(Plane& plane, sf::RenderWindow& window);

  void Update(const sf::Event& event) override;

 private:
  enum class Action
  {
    kCreatePoint
  };

  void InitActionMap();

  void CreatePoint();

  /*
   * Member data.
   */
  thor::ActionMap<Action> action_map_;

  sf::RenderWindow& window_;

  PointFactory factory_;
};

class CreationDirector
{
 public:
  explicit CreationDirector(std::unique_ptr<Creator>&& creator);

  void Update(const sf::Event& event) const;

 private:
  /**
   * Member data.
   */
  size_t step_ = 0;
  std::unique_ptr<Creator> creator_{nullptr};
};
