#pragma once
#include <utility>

#include "Assert.h"

/**
 * \brief Checks if object has method SetArgument.
 *
 * \tparam T Type of object.
 * \tparam Arg Type of argument.
 */
template <class T, class Arg>
concept HasSetArgument =
    requires(T t, Arg&& arg) { t.SetArgument(std::forward<Arg>(arg)); };

/**
 * \brief Wrapper of element
 *
 * \tparam Element Element to wrap.
 * \tparam index Index.
 */
template <class Element, size_t index = 0>
class Wrapper
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  Wrapper() = default;

  /**
   * \brief Constructor by element constructor.
   *
   * \tparam T Constructor argument type.
   * \param arg Constructor argument.
   */
  template <class T>
    requires(!std::same_as<Wrapper<Element, index>, std::remove_cvref_t<T>>)
  explicit Wrapper(T&& arg);

  /**
   * \brief Call operator() with args.
   *
   * \tparam Args Argument types.
   * \param args Arguments.
   *
   * \return Result of call operator() of element.
   */
  template <class... Args>
  auto operator()(Args&&... args);

  /**
   * \brief Set argument.
   *
   * \tparam Arg Argument type.
   * \param arg Argument.
   */
  template <class Arg>
    requires HasSetArgument<Element, Arg>
  void SetArgument(Arg&& arg);

  /**
   * \brief Check if element is set.
   *
   * \return True if element is set, false otherwise.
   */
  [[nodiscard]] bool IsSet();

 private:
  Element element_;  //!< Wrapped element.
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
template <class First, class... Rest>
class ObjectConstructor : public Wrapper<First, sizeof...(Rest)>,
                          public ObjectConstructor<Rest...>
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  ObjectConstructor();

  /**
   * \brief Constructor by element constructor.
   *
   * \tparam Head Type of head.
   * \tparam Tail Types of tail.
   * \param head Head.
   * \param tail Tail.
   */
  template <class Head, class... Tail>
    requires(!std::same_as<ObjectConstructor<First, Rest...>,
                           std::remove_cvref_t<Head>>)
  explicit ObjectConstructor(Head&& head, Tail&&... tail);

  /**
   * \brief Construct object from arguments.
   *
   * \details Gets arguments and passes them to last element.
   *
   * \tparam Args Argument types.
   * \param arguments Already received arguments.
   */
  template <class... Args>
  void ConstructObject(Args&&... arguments);

  /**
   * \brief Set argument.
   *
   * \tparam Arg Argument type.
   * \param arg Argument.
   */
  template <class Arg>
    requires HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>
  void SetArgument(Arg&& arg);

  /**
   * \brief Skips setting argument.
   *
   * \details If element doesn`t have SetArgument method, it skips it.
   *
   * \tparam Arg Argument type.
   * \param arg Argument.
   */
  template <class Arg>
    requires(!HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>)
  void SetArgument(Arg&& arg);
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
template <class First>
class ObjectConstructor<First> : public Wrapper<First, 0>
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  ObjectConstructor();

  /**
   * \brief Constructor by element constructor.
   *
   * \tparam Arg Constructor argument type.
   * \param arg Constructor argument.
   */
  template <class Arg>
    requires(!std::same_as<ObjectConstructor<First>, std::remove_cvref_t<Arg>>)
  explicit ObjectConstructor(Arg&& arg);

  /**
   * \brief Construct object from arguments.
   *
   * \tparam Args Argument types.
   * \param arguments Already received arguments.
   */
  template <class... Args>
  void ConstructObject(Args&&... arguments);
};

template <class Element, size_t index>
template <class T>
  requires(!std::same_as<Wrapper<Element, index>, std::remove_cvref_t<T>>)
Wrapper<Element, index>::Wrapper(T&& arg) : element_(std::forward<T>(arg))
{}

template <class Element, size_t index>
template <class... Args>
auto Wrapper<Element, index>::operator()(Args&&... args)
{
  return element_(std::forward<Args>(args)...);
}

template <class Element, size_t index>
template <class Arg>
  requires HasSetArgument<Element, Arg>
void Wrapper<Element, index>::SetArgument(Arg&& arg)
{
  element_.SetArgument(std::forward<Arg>(arg));
}

template <class Element, size_t index>
bool Wrapper<Element, index>::IsSet()
{
  return element_.IsSet();
}

template <class First, class... Rest>
ObjectConstructor<First, Rest...>::ObjectConstructor()
    : Wrapper<First, sizeof...(Rest)>(), ObjectConstructor<Rest...>()
{}

template <class First, class... Rest>
template <class Head, class... Tail>
  requires(!std::same_as<ObjectConstructor<First, Rest...>,
                         std::remove_cvref_t<Head>>)
ObjectConstructor<First, Rest...>::ObjectConstructor(Head&& head,
                                                     Tail&&... tail)
    : Wrapper<First, sizeof...(Rest)>(std::forward<Head>(head)),
      ObjectConstructor<Rest...>(std::forward<Tail>(tail)...)
{}

template <class First, class... Rest>
template <class... Args>
void ObjectConstructor<First, Rest...>::ConstructObject(Args&&... arguments)
{
  ObjectConstructor<Rest...>::ConstructObject(
      std::forward<Args>(arguments)...,
      Wrapper<First, sizeof...(Rest)>::operator()());
}

template <class First, class... Rest>
template <class Arg>
  requires HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>
void ObjectConstructor<First, Rest...>::SetArgument(Arg&& arg)
{
  if (!(Wrapper<First, sizeof...(Rest)>::IsSet()))
  {
    Wrapper<First, sizeof...(Rest)>::SetArgument(std::forward<Arg>(arg));
  }
  else
  {
    if constexpr (HasSetArgument<ObjectConstructor<Rest...>, Arg>)
      ObjectConstructor<Rest...>::SetArgument(std::forward<Arg>(arg));
    else
      assert(false);
  }
}

template <class First, class... Rest>
template <class Arg>
  requires(!HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>)
void ObjectConstructor<First, Rest...>::SetArgument(Arg&& arg)
{
  if constexpr (HasSetArgument<ObjectConstructor<Rest...>, Arg>)
    ObjectConstructor<Rest...>::SetArgument(std::forward<Arg>(arg));
  else
    assert(false);
}

template <class First>
ObjectConstructor<First>::ObjectConstructor() : Wrapper<First, 0>()
{}

template <class First>
template <class Arg>
  requires(!std::same_as<ObjectConstructor<First>, std::remove_cvref_t<Arg>>)
ObjectConstructor<First>::ObjectConstructor(Arg&& arg)
    : Wrapper<First, 0>(std::forward<Arg>(arg))
{}

template <class First>
template <class... Args>
void ObjectConstructor<First>::ConstructObject(Args&&... arguments)
{
  Wrapper<First, 0>::operator()(std::forward<Args>(arguments)...);
}
