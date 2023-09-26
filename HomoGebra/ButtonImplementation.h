#pragma once
#include <utility>

#include "Plane.h"

namespace HomoGebra
{
template <class T>
concept ButtonElement = requires(T button_part) {
                          {
                            T{new Plane{}}
                          };
                          {
                            button_part.Draw()
                          };
                        } && requires(const T button_part) {
                               {
                                 button_part()
                               };
                             };

/**
 * \brief Wrapper of element
 *
 * \tparam Element Element to wrap.
 * \tparam index Index.
 */
template <class Element, size_t index = 0>
struct Wrapper : Element
{
  explicit Wrapper(Plane* plane) : Element(plane) {}
};

/**
 * \brief Button implementation.
 *
 *
 * \tparam First First element type.
 * \tparam Rest Rest elements types.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
template <ButtonElement First, class... Rest>
class ButtonImplementation : public Wrapper<First, sizeof...(Rest)>,
                             public ButtonImplementation<Rest...>
{
 public:
  /**
   * \brief Construct button for plane.
   *
   * \param plane Plane to construct button for.
   */
  explicit ButtonImplementation(Plane* plane)
      : Wrapper<First, sizeof...(Rest)>(plane),
        ButtonImplementation<Rest...>(plane)
  {}

  /**
   * \brief Draws button.
   *
   */
  void Draw()
  {
    Wrapper<First, sizeof...(Rest)>::Draw();
    ButtonImplementation<Rest...>::Draw();
  }

  /**
   * \brief Construct object from arguments.
   *
   * \tparam Args Argument types.
   * \param arguments Already received arguments.
   */
  template <class... Args>
  void PassArguments(Args&&... arguments);
};

/**
 * \brief Object constructor for one element.
 *
 * \details Tail of ObjectConstructor.
 *
 * \tparam First First element type.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
template <ButtonElement First>
class ButtonImplementation<First> : public Wrapper<First, 0>
{
 public:
  /**
   * \brief Construct button for plane.
   *
   * \param plane Plane to construct button for.
   */
  explicit ButtonImplementation(Plane* plane) : Wrapper<First>(plane) {}

  /**
   * \brief Draws button.
   *
   */
  void Draw() { Wrapper<First>::Draw(); }

  /**
   * \brief Construct object from arguments.
   *
   * \tparam Args Argument types.
   * \param arguments Already received arguments.
   */
  template <class... Args>
  void PassArguments(Args&&... arguments);
};

template <ButtonElement First, class... Rest>
template <class... Args>
void ButtonImplementation<First, Rest...>::PassArguments(Args&&... arguments)
{
  ButtonImplementation<Rest...>::PassArguments(
      std::forward<Args>(arguments)...,
      Wrapper<First, sizeof...(Rest)>::operator()());
}

template <ButtonElement First>
template <class... Args>
void ButtonImplementation<First>::PassArguments(Args&&... arguments)
{
  Wrapper<First, 0>::operator()(std::forward<Args>(arguments)...);
}
}  // namespace HomoGebra
