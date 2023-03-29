#pragma once
#include <Thor/Input.hpp>

#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "Plane.h"

/**
 * \brief Base class for creators of geometric objects using mouse.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 */
class Creator
{
 public:
  /**
   * \brief Default destructor.
   *
   */
  virtual ~Creator() = default;

  /**
   * \brief Updates the creator.
   *
   * \param event Event to process.
   */
  virtual void Update(const sf::Event& event) = 0;
};

/**
 * \brief Creator of points.
 *
 * \detail Click once to create a point.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class PointCreator final : public Creator
{
 public:
  /**
   * \brief Constructor.
   *
   * \param plane Plane, where the point will be created.
   * \param window Window, where the point will be created.
   */
  PointCreator(Plane& plane, sf::RenderWindow& window);

  /**
   * \brief Updates the creator.
   *
   * \param event Event to process.
   */
  void Update(const sf::Event& event) override;

 private:
  /**
   * \brief Actions that can be performed by the user.
   *
   */
  enum class Action
  {
    kCreatePoint
  };

  /**
   * \brief Initializes the action map.
   *
   */
  void InitActionMap();

  /**
   * \brief Creates a point.
   *
   */
  void CreatePoint();

  /*
   * Member data.
   */
  thor::ActionMap<Action> action_map_;  //!< Map with actions that user do.

  sf::RenderWindow& window_;  //!< Window, where the point will be created.

  PointFactory factory_;  //!< Factory for creating points.
};

/**
 * \breif Director of creation of geometric objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class CreationDirector
{
 public:
  /**
   * \brief Constructor.
   *
   */
  explicit CreationDirector(
      std::unique_ptr<Creator>&& creator = std::unique_ptr<Creator>{nullptr});

  void Update(const sf::Event& event) const;

 private:
  /**
   * Member data.
   */
  size_t step_ = 0;
  std::unique_ptr<Creator> creator_{nullptr};
};
