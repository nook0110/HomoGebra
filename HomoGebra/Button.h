#pragma once
#include "ButtonBody.h"
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
class ButtonBase : public ButtonImplementation<Elements...>, public ButtonBody
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
    if (ButtonBody::Draw())
    {
      ButtonImplementation<Elements...>::PassArguments();
    }
  }
};
}  // namespace HomoGebra
