#pragma once
#include <imgui.h>

#include "ButtonImplementation.h"
namespace HomoGebra
{
/**
 * \brief Button.
 *
 * \see LineByTwoPointButton
 * \see DeleteButton
 *
 */
template <class... Elements>
class ButtonBase : public ButtonImplementation<Elements...>
{
 public:
  /**
   * \brief Construct button for plane.
   *
   */
  explicit ButtonBase(Plane* plane) : ButtonImplementation<Elements...>(plane)
  {}

  /**
   * \brief Draws button.
   *
   */
  void Draw()
  {
    ButtonImplementation<Elements...>::Draw();
    if (DrawApplyButton())
    {
      ButtonImplementation<Elements...>::PassArguments();
    }
  }

 private:
  /**
   * \brief Draws the apply button.
   *
   * \return True if the apply button is pressed, false otherwise.
   */
  bool DrawApplyButton() { return ImGui::Button("Apply"); }
};
}  // namespace HomoGebra
