#pragma once
#include <utility>

#include "Assert.h"

template <class T, class Arg>
concept HasSetArgument =
    requires(T t, Arg&& arg) { t.SetArgument(std::forward<Arg>(arg)); };

template <class Element, size_t index = 0>
class Wrapper
{
 public:
  Wrapper() = default;

  template <class T>
    requires(!std::same_as<Wrapper<Element, index>, std::remove_cvref_t<T>>)
  explicit Wrapper(T&& arg);

  template <class... Args>
  auto operator()(Args&&... args);

  template <class Arg>
    requires HasSetArgument<Element, Arg>
  void SetArgument(Arg&& arg);

 private:
  Element element_;
};

template <class First, class... Rest>
class Button : public Wrapper<First, sizeof...(Rest)>, public Button<Rest...>
{
 public:
  Button();

  template <class Head, class... Tail>
    requires(!std::same_as<Button<First, Rest...>, std::remove_cvref_t<Head>>)
  explicit Button(Head&& head, Tail&&... tail);

  template <class... Args>
  void ConstructObject(Args&&... arguments);

  template <class Arg>
    requires HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>
  void SetArgument(Arg&& arg);

  template <class Arg>
    requires(!HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>)
  void SetArgument(Arg&& arg);
};

template <class First>
class Button<First> : public Wrapper<First, 0>
{
 public:
  Button();

  template <class... Args>
  void ConstructObject(Args&&... arguments);

  template <class Arg>
    requires HasSetArgument<Wrapper<First, 0>, Arg>
  void SetArgument(Arg&& arg);

  template <class Arg>
    requires(!HasSetArgument<Wrapper<First, 0>, Arg>)
  void SetArgument(Arg&& arg);
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

template <class First, class... Rest>
Button<First, Rest...>::Button()
    : Wrapper<First, sizeof...(Rest)>(), Button<Rest...>()
{}

template <class First, class... Rest>
template <class Head, class... Tail>
  requires(!std::same_as<Button<First, Rest...>, std::remove_cvref_t<Head>>)
Button<First, Rest...>::Button(Head&& head, Tail&&... tail)
    : Wrapper<First, sizeof...(Rest)>(std::forward<Head>(head)),
      Button<Rest...>(std::forward<Tail>(tail)...)
{}

template <class First, class... Rest>
template <class... Args>
void Button<First, Rest...>::ConstructObject(Args&&... arguments)
{
  Button<Rest...>::ConstructObject(
      std::forward<Args>(arguments)...,
      Wrapper<First, sizeof...(Rest)>::operator()());
}

template <class First, class... Rest>
template <class Arg>
  requires HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>
void Button<First, Rest...>::SetArgument(Arg&& arg)
{
  Wrapper<First, 0>::SetArgument(std::forward<Arg>(arg));
}

template <class First, class... Rest>
template <class Arg>
  requires(!HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>)
void Button<First, Rest...>::SetArgument(Arg&& arg)
{
  Button<Rest...>::SetArgument(std::forward<Arg>(arg));
}

template <class First>
Button<First>::Button() : Wrapper<First, 0>()
{}

template <class First>
template <class... Args>
void Button<First>::ConstructObject(Args&&... arguments)
{
  Wrapper<First, 0>::operator()(std::forward<Args>(arguments)...);
}

template <class First>
template <class Arg>
  requires HasSetArgument<Wrapper<First, 0>, Arg>
void Button<First>::SetArgument(Arg&& arg)
{
  Wrapper<First, 0>::SetArgument(std::forward<Arg>(arg));
}

template <class First>
template <class Arg>
  requires(!HasSetArgument<Wrapper<First, 0>, Arg>)
void Button<First>::SetArgument(Arg&& arg)
{
  Expect(false, "No argument was updated!");
}
