#pragma once
#include "Button.h"
#include "ButtonElement.h"
#include "GeometricObjectFactory.h"
#include "imgui.h"

namespace HomoGebra
{
/**
 * @brief A class representing a window button.
 *
 * This class is a template class that inherits from a specified button class.
 * It provides functionality to draw a button inside an ImGui window.
 *
 * @tparam ButtonClass The class of the button to inherit from.
 */
template <class ButtonClass>
class WindowButton : public ButtonClass
{
 public:
  /**
   * @brief Constructs a new WindowButton object.
   *
   * @param name The name of the button.
   * @param plane The plane associated with the button.
   */
  explicit WindowButton(std::string name, Plane* plane)
      : ButtonClass(plane), name_(std::move(name))
  {}

  /**
   * @brief Draws the button inside an ImGui window.
   */
  void Draw()
  {
    ImGui::Begin(name_.data());
    ButtonClass::Draw();
    ImGui::End();
  }

 private:
  std::string name_; /**< The name of the button. */
};

/**
 * @brief A class representing a button for creating a line by two points.
 *
 * This class is a specialization of the WindowButton class.
 * It provides functionality to create a line by selecting two points on a
 * plane.
 */
class LineByTwoPointButton final
    : public WindowButton<
          ButtonBase<ObjectSelector<Point>, ObjectSelector<Point>,
                     FactoryWrapper<LineByTwoPointsFactory>>>
{
 public:
  /**
   * @brief Constructs a new LineByTwoPointButton object.
   *
   * @param plane The plane associated with the button.
   */
  explicit LineByTwoPointButton(Plane* plane)
      : WindowButton("Line by two points", plane)
  {}
};

/**
 * @brief A class representing a delete button.
 *
 * This class is a specialization of the WindowButton class.
 * It provides functionality to delete a selected geometric object.
 */
class DeleteButton final
    : public WindowButton<ButtonBase<ObjectSelector<GeometricObject>, Deleter>>
{
 public:
  /**
   * @brief Constructs a new DeleteButton object.
   *
   * @param plane The plane associated with the button.
   */
  explicit DeleteButton(Plane* plane) : WindowButton("Delete button", plane) {}
};
}  // namespace HomoGebra
