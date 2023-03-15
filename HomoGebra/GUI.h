#pragma once

#include "GeometricObject.h"
#include "Plane.h"
#include "SFML/Graphics.hpp"

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
class ObjectMenu final : public ImGuiWindow
{
 public:
  class HomogeneousCoordinateEditor
  {
   public:
    explicit HomogeneousCoordinateEditor(
        const HomogeneousCoordinate& coordinate = HomogeneousCoordinate{});

    void Construct();

    [[nodiscard]] HomogeneousCoordinate GetCoordinate() const;

   private:
    class ComplexEditor
    {
     public:
      explicit ComplexEditor(const Complex& number = Complex{});

      void Construct();

      [[nodiscard]] Complex GetNumber() const;

     private:
      double real_part_;
      double imaginary_part_;
    };
    ComplexEditor x_variable_editor_;
    ComplexEditor y_variable_editor_;
    ComplexEditor z_variable_editor_;
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
    /**
     * Member data.
     */
    HomogeneousCoordinateEditor
        coordinate_editor_;         //!< Editor for coordinates.
    std::shared_ptr<Point> point_;  //!< Point to edit.
  };

  explicit ObjectMenu(Plane& plane) : plane_(plane) {}

  void Construct() final;

 private:
  /**
   * Member data.
   */
  Plane& plane_;  //!< Plane which we can edit.
};
}  // namespace Gui