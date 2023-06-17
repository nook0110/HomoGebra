#pragma once
#include "Complex.h"
#include "GeometricObject.h"
#include "Input.h"

namespace Gui
{
/**
 * \brief Getter for objects names.
 *
 * \param [in] data Pointer to the vector of objects.
 * \param [in] index Index of the object.
 * \param [out] name Name of the object.
 *
 * \return True if the object exists, false otherwise.
 */
inline bool ObjectsNameGetter(void* data, int index, const char** name)
{
  // Convert data to std::vector<GeometricObject*> pointer
  const std::vector<GeometricObject*>& objects =
      *static_cast<std::vector<GeometricObject*>*>(data);

  // Check if index is valid
  if (index < 0 || index >= static_cast<int>(objects.size()))
  {
    return false;
  }

  // Set name
  *name = objects[index]->GetName().data();

  return true;
}

/**
 * \brief Mix-In for widgets.
 *
 * \author nook0110
 */
class Widget
{
 public:
  /**
   * \brief Default destructor.
   *
   */
  virtual ~Widget() = default;

  /**
   * \brief Constructs widget.
   *
   */
  virtual void Construct() = 0;
};

namespace Editor
{
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
class ComplexEditor final : public Widget
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
 * \brief Class that represents a submenu that allows to edit a homogeneous
 * coordinates.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class HomogeneousCoordinateEditor final : public Widget
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
class PointSubmenu : public Widget
{
 public:
  /**
   * \brief Construct menu with given point.
   *
   * \param plane Plane where point is located.
   * \param point Point to edit.
   */
  explicit PointSubmenu(Plane& plane, Point* point = nullptr);

  /**
   * \brief Sets new point to edit.
   *
   * \param point New point to edit.
   */
  void SetPoint(Point* point);

  /**
   * \brief Renders the menu.
   *
   */
  void Construct();

 private:
  /**
   * \brief Render name editor.
   *
   */
  void ConstructNameEditor();

  /**
   * \brief Render name suggestions.
   *
   */
  void ConstructNameSuggestions();

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

  std::string name_;                               //!< Name of the point.
  HomogeneousCoordinateEditor coordinate_editor_;  //!< Editor for coordinates
  Point* point_;                                   //!< Point to edit.
  Plane& plane_;  //!< Plane where point is located.
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
class ObjectMenu final : public Widget
{
 public:
  /**
   * \brief Constructs a menu for given plane and name.
   *
   * \param plane Plane to edit.
   */
  ObjectMenu(Plane& plane) : point_submenu_(plane), plane_(plane) {}

  void Construct();

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
  [[nodiscard]] std::vector<GeometricObject*> GetObjectsOfType(
      const ObjectType type) const;

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
  void Construct(GeometricObject* object);

  /**
   * \brief Constructs editor of point.
   *
   * \param point Point to edit.
   */
  void Construct(Point* point);

  /**
   * \brief Constructs editor of line.
   *
   * \param line Object to edit.
   */
  void Construct(Line* line);

  /**
   * \brief Constructs editor of conic.
   *
   * \param conic Line to edit.
   */
  void Construct(Conic* conic);

  /**
   * Member data.
   */
  int current_type_ = static_cast<int>(ObjectType::kAll);

  Editor::PointSubmenu point_submenu_;  //!< Submenu for points.

  Plane& plane_;  //!< Plane which we can edit.
};

namespace Constructor
{
/**
 * \brief Widget to select object.
 *
 * \details By name or nearest to last click object.
 *
 * \tparam GeometricObjectType Type of object to select.
 *
 * \author nook0110
 */
template <class GeometricObjectType>
class ObjectSelector : public Widget, public EventListener
{
 public:
  /**
   * \brief Constructor.
   *
   * \param plane Plane where to select object.
   * \param window Window where clicks are happening.
   *
   */
  explicit ObjectSelector(Plane& plane, sf::RenderWindow& window)
      : plane_(plane), object_getter_(plane, window)
  {}

  /**
   * \brief Get selected object.
   *
   * \return Pointer to selected object.
   */
  [[nodiscard]] GeometricObjectType* GetObject() const;

  /**
   * \brief Set selected object.
   *
   * \param object Object to set with.
   */
  void SetObject(GeometricObjectType* object);

  /**
   * \brief Constructs the widget.
   *
   */
  void Construct() override;

  void Update(const UserEvent::Clicked& event) override;

 private:
  /**
   * \brief Constructs name of selected object.
   *
   */
  void ConstructSelectedObject();

  /**
   * \brief Construct list to choose object from.
   *
   */
  void ConstructList();

  /**
   * \brief Construct setter through last nearest object.
   *
   */
  void ConstructSetter();

  Plane& plane_;                   //!< Plane where to choose objects.
  GeometricObjectType* object_{};  //!< Object that was selected.
  NearbyObjectGetter<GeometricObjectType>
      object_getter_;  //!< Helper to find specific objects.

  int current_object_ = 0;  //!< Index in list of all objects.
};
}  // namespace Constructor
}  // namespace Gui