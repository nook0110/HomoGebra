#pragma once

#include <vector>

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
class EditorWindow
{
 public:
  /**
   * \brief Default constructor.
   *
   * \param name Name of the window.
   */
  explicit EditorWindow(std::string name) : name_(std::move(name)) {}

  /**
   * \brief Default destructor.
   *
   */
  virtual ~EditorWindow() = default;

  /**
   * \brief Begins constructing the window.
   *
   */
  void Begin() const;

  /**
   * \brief Ends constructing the window.
   *
   */
  void End() const;

  /**
   * \brief Constructs the window
   */
  virtual void Construct() = 0;

 private:
  std::string name_;  //!< Name of the window.
};

namespace Editor
{
/**
 * \brief Class that represents a submenu that allows to edit a homogeneous
 * coordinates.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class HomogeneousCoordinateEditor
{
 public:
  /**
   * \brief Construct menu with given coordinate.
   *
   * \param coordinate Coordinate to edit.
   */
  explicit HomogeneousCoordinateEditor(
      const HomogeneousCoordinate& coordinate = HomogeneousCoordinate{});

  /**
   * \brief Renders the menu.
   *
   */
  void Construct();

  /**
   * \brief Renders the menu.
   *
   */
  void Construct() const;

  /**
   * \brief Returns the current coordinate that was edited.
   *
   * \return Current coordinate.
   */
  [[nodiscard]] HomogeneousCoordinate GetCoordinate() const;

 private:
  /**
   * \brief Class that represents a submenu that allows to edit a complex
   * number
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date February 2023
   */
  class ComplexEditor
  {
   public:
    /**
     * \brief Construct menu with given number.
     *
     * \param number Number to edit.
     */
    explicit ComplexEditor(const Complex& number = Complex{});

    /**
     * \brief Renders the menu.
     *
     */
    void Construct();

    /**
     * \brief Renders the menu.
     *
     */
    void Construct() const;

    /**
     * \brief Returns the current number that was edited.
     *
     * \return Current number.
     */
    [[nodiscard]] Complex GetNumber() const;

   private:
    double real_part_;       //!< Real part of the number.
    double imaginary_part_;  //!< Imaginary part of the number.
  };
  /**
   * Member data.
   */
  ComplexEditor x_variable_editor_;  //!< Editor for x variable.
  ComplexEditor y_variable_editor_;  //!< Editor for y variable.
  ComplexEditor z_variable_editor_;  //!< Editor for z variable.
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
 public:
  /**
   * \brief Construct menu with given point.
   *
   * \param point Point to edit.
   */
  explicit PointSubmenu(const std::shared_ptr<Point>& point);

  /**
   * \brief Sets new point to edit.
   *
   * \param point New point to edit.
   */
  void SetPoint(const std::shared_ptr<Point>& point);

  /**
   * \brief Renders the menu.
   *
   */
  void Construct();

 private:
  void ConstructNameEditor();

  /**
   * \brief Render variables, that can be edited.
   *
   */
  void ConstructEditableValues();

  /**
   * \brief Render current variables
   *
   */
  void ConstructCurrentValues() const;

  /**
   * Member data.
   */
  std::string name_;
  HomogeneousCoordinateEditor coordinate_editor_;  //!< Editor for coordinates
  std::shared_ptr<Point> point_;                   //!< Point to edit.
};
}  // namespace Editor

/**
 * \brief Class that represents a window that allows to edit objects.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class ObjectMenu final : public EditorWindow
{
 public:
  /**
   * \brief Constructs a menu for given plane and name.
   *
   * \param plane Plane to edit.
   * \param name Name of the menu.
   */
  explicit ObjectMenu(Plane& plane, const std::string& name)
      : EditorWindow(name), plane_(plane)
  {}

  void Construct() override;

 private:
  /**
   * \enum ObjectType Type of object
   *
   * \var ObjectType::kAll
   * All objects (similar to GeometricObject)
   *
   * \var ObjectType::kPoint
   * Only points (similar to Point)
   *
   * \var ObjectType::kLine
   * Only lines (similar to Line)
   *
   * \var ObjectType::kConic
   * Only conics (similar to Conic)
   */
  enum class ObjectType : int
  {
    kAll,
    kPoint,
    kLine,
    kConic
  };

  static constexpr std::array<const char*, 4> kTypesOfObjects = {
      "All", "Points", "Lines", "Conics"};  //!< Names of types of objects.

  /**
   * \brief Getter for objects of given type.
   *
   * \param type Type of the object.
   *
   * \return Vector of objects of given type.
   */
  [[nodiscard]] std::vector<std::shared_ptr<GeometricObject>> GetObjectsOfType(
      const ObjectType type) const;

  /**
   * \brief Getter for objects names.
   *
   * \param [in] data Pointer to the vector of objects.
   * \param [in] index Index of the object.
   * \param [out] name Name of the object.
   *
   * \return True if the object exists, false otherwise.
   */
  static bool ObjectsNameGetter(void* data, int index, const char** name);

  /**
   * \brief Constructs menu to select object by name.
   *
   */
  void ConstructObjectSelector();

  /**
   * \brief Constructs menu to select object by name.
   *
   * \tparam GeometricObjectType Type of the object.
   */
  template <class GeometricObjectType>
  void ConstructObjectSelector();

  /**
   * \brief Constructs editor of object.
   *
   * \param object Object to edit.
   */
  void Construct(const std::shared_ptr<GeometricObject>& object);

  /**
   * \brief Constructs editor of point.
   *
   * \param point Point to edit.
   */
  void Construct(const std::shared_ptr<Point>& point);

  /**
   * \brief Constructs editor of line.
   *
   * \param line Object to edit.
   */
  void Construct(const std::shared_ptr<Line>& line);

  /**
   * \brief Constructs editor of conic.
   *
   * \param conic Line to edit.
   */
  void Construct(const std::shared_ptr<Conic>& conic);

  /**
   * Member data.
   */
  int current_type_ = static_cast<int>(ObjectType::kAll);

  int current_object_ = 0;  //!< Index of the current object.

  Editor::PointSubmenu point_submenu_{nullptr};  //!< Submenu for points.

  Plane& plane_;  //!< Plane which we can edit.
};
}  // namespace Gui