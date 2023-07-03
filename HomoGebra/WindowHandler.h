#pragma once

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

/**
 * \brief Gui window.
 *
 * \details Just widget that creates it own window with name.
 *
 * \see Gui::Widget
 */
class Window
{
 public:
  /**
   * \brief Constructor.
   *
   * \param name Name of window.
   * \param widget Widget to wrap.
   */
  Window(std::string name, std::unique_ptr<Widget> widget)
      : name_(std::move(name)), widget_(std::move(widget))
  {}

  /**
   * \brief Constructs window.
   *
   */
  void Draw();

  /**
   * \brief Gets object
   *
   * \return Wrapped widget.
   *
   */
  [[nodiscard]] Widget* GetWidget() const;

 private:
  /**
   * \brief Starts constructing of ImGui window.
   *
   */
  void Begin() const;

  /**
   * \brief Ends construction of ImGui window.
   *
   */
  void End() const;

  std::string name_;  //!< Name of the window.

  std::unique_ptr<Widget> widget_;  //!< Widget which was wrapped.
};

/**
 * \brief Class that handles Gui::Window-s
 *
 * \see Gui::Window
 *
 * \author nook0110
 */
class WindowHandler
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  WindowHandler() = default;

  /**
   * \brief Default destructor.
   *
   */
  ~WindowHandler() = default;

  /**
   * \brief Constructs all Gui::Window-s
   *
   */
  void Construct();

  /**
   * \brief Adds window to list.
   *
   * \param window Window to add.
   */
  void AddWindow(std::unique_ptr<Window> window);

  /**
   * \brief Deletes window from list.
   *
   * \param window Window to delete.
   */
  void DeleteWindow(Window* window);

 private:
  std::list<std::unique_ptr<Window>> windows_;  //!< All windows to render.
};
}  // namespace Gui