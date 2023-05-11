#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "Widget.h"

namespace Gui
{
/**
 * \brief Global functions needed for Dear ImGui to work.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Wraps Dear ImGui global methods and a clock for rendering.
 *
 * \see <a href="https://github.com/ocornut/imgui">Dear ImGui</a>
 * \see <a href="https://github.com/eliasdaler/imgui-sfml">ImGui-SFML v2.5</a>
 */
class Global
{
 public:
  /**
   * \brief Updates all Dear ImGui windows in sf::RenderWindow instance.
   *
   * \param window sf::RenderWindow where to update Dear ImGui windows.
   */
  static void Update(sf::RenderWindow& window);
  /**
   * \brief Renders all Dear ImGui windows in sf::RenderWindow instance.
   *
   * \param window sf::RenderWindow where to render Dear ImGui windows.
   */
  static void Render(sf::RenderWindow& window);
  /**
   * \brief Process event happened to update Dear ImGui windows.
   *
   * \param event Event that happened.
   */
  static void ProcessEvent(const sf::Event& event);

 private:
  /**
   * Static member data.
   */
  static sf::Clock delta_clock_;  //!< Clock that counts time for updates.
};

class Constructable
{
 public:
  virtual ~Constructable() = default;
  virtual void Construct() = 0;
};

class GuiHandler : public Constructable
{
 public:
  explicit GuiHandler(sf::RenderWindow& window);

  ~GuiHandler() = default;

  void Construct() override;

  void AddConstructable(std::unique_ptr<Constructable> constructable);

  void DeleteConstructable(Constructable* constructable);

 private:
  static std::unique_ptr<GuiHandler> instance_;

  sf::RenderWindow& window_;

  std::list<std::unique_ptr<Constructable>> constructable_objects_;
};

class Window final : public Constructable
{
 public:
  Window(std::string name, std::unique_ptr<Widget> widget)
      : name_(std::move(name)), widget_(std::move(widget))
  {}

  void Construct() override;

 private:
  void Begin() const;
  void End() const;

  std::string name_;

  std::unique_ptr<Widget> widget_;
};
}  // namespace Gui