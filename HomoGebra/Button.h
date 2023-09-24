#pragma once
#include <utility>

#include "ButtonBody.h"
#include "Plane.h"

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
 * \brief Object constructor.
 *
 * \details Constructs object from elements. Which are usually Selector-s or
 * Factories.
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
  explicit ButtonImplementation(Plane* plane)
      : Wrapper<First, sizeof...(Rest)>(plane),
        ButtonImplementation<Rest...>(plane)
  {}

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
  void ConstructObject(Args&&... arguments);
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
  explicit ButtonImplementation(Plane* plane) : Wrapper<First>(plane) {}

  void Draw() { Wrapper<First>::Draw(); }

  /**
   * \brief Construct object from arguments.
   *
   * \tparam Args Argument types.
   * \param arguments Already received arguments.
   */
  template <class... Args>
  void ConstructObject(Args&&... arguments);
};

template <ButtonElement First, class... Rest>
template <class... Args>
void ButtonImplementation<First, Rest...>::ConstructObject(Args&&... arguments)
{
  ButtonImplementation<Rest...>::ConstructObject(
      std::forward<Args>(arguments)...,
      Wrapper<First, sizeof...(Rest)>::operator()());
}

template <ButtonElement First>
template <class... Args>
void ButtonImplementation<First>::ConstructObject(Args&&... arguments)
{
  Wrapper<First, 0>::operator()(std::forward<Args>(arguments)...);
}

template <class... Elements>
class Button : public ButtonImplementation<Elements...>, public ButtonBody
{
 public:
  explicit Button(Plane* plane) : ButtonImplementation<Elements...>(plane) {}

  void Draw()
  {
    ButtonImplementation<Elements...>::Draw();
    if (ButtonBody::Draw())
    {
      ButtonImplementation<Elements...>::ConstructObject();
    }
  }
};
