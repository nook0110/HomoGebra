#pragma once

#include "GeometricObject.h"
#include "Plane.h"
#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace GUI
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
  static void ProcessEvent(sf::Event event);

 private:
  /**
   * Static member data.
   */
  static sf::Clock deltaClock;  //!< Clock that counts time for updates.
};

/**
 * \brief Interface that represents a window in Dear ImGui.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class ImGuiWindow
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  ImGuiWindow() = default;

  virtual ~ImGuiWindow() = default;

  void Begin() const;

  void End() const;

  /**
   * \brief Constructs the window
   */
  virtual void Construct() = 0;

 private:
  std::string name;  //!< Name of the window.
};

/**
 * \brief Class that represents a window that allows to edit objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class ObjectMenu : public ImGuiWindow
{
 public:
  explicit ObjectMenu(Plane& plane) : plane(plane) {}

  void Construct() final;

 private:
  class HomogeneousCoordinateEditor
  {
   public:
    explicit HomogeneousCoordinateEditor(HomogeneousCoordinate& coordinate);
    const HomogeneousCoordinate& GetCoordinate();

   private:
    HomogeneousCoordinate coordinate;
  };

  /**
   * \brief Class that represents a submenu that allows to edit points.
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date February 2023
   */
  class PointSubmenu
  {
   private:
  };

  /**
   * Member data.
   */
  Plane& plane;  //!< Plane which we can edit.
};
}  // namespace GUI