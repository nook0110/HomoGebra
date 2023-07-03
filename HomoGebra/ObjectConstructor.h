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

  [[nodiscard]] bool IsSet();

 private:
  Element element_;
};

template <class First, class... Rest>
class ObjectConstructor : public Wrapper<First, sizeof...(Rest)>,
                          public ObjectConstructor<Rest...>
{
 public:
  ObjectConstructor();

  template <class Head, class... Tail>
    requires(!std::same_as<ObjectConstructor<First, Rest...>,
                           std::remove_cvref_t<Head>>)
  explicit ObjectConstructor(Head&& head, Tail&&... tail);

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
class ObjectConstructor<First> : public Wrapper<First, 0>
{
 public:
  ObjectConstructor();

  template <class Arg>
    requires(!std::same_as<ObjectConstructor<First>, std::remove_cvref_t<Arg>>)
  explicit ObjectConstructor(Arg&& head);

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
    Wrapper<First, sizeof...(Rest)>::SetArgument(std::forward<Arg>(arg));
  else
    ObjectConstructor<Rest...>::SetArgument(std::forward<Arg>(arg));
}

template <class First, class... Rest>
template <class Arg>
  requires(!HasSetArgument<Wrapper<First, sizeof...(Rest)>, Arg>)
void ObjectConstructor<First, Rest...>::SetArgument(Arg&& arg)
{
  ObjectConstructor<Rest...>::SetArgument(std::forward<Arg>(arg));
}

template <class First>
ObjectConstructor<First>::ObjectConstructor() : Wrapper<First, 0>()
{}

template <class First>
template <class Arg>
  requires(!std::same_as<ObjectConstructor<First>, std::remove_cvref_t<Arg>>)
ObjectConstructor<First>::ObjectConstructor(Arg&& head)
    : Wrapper<First, 0>(std::forward<Arg>(head))
{}

template <class First>
template <class... Args>
void ObjectConstructor<First>::ConstructObject(Args&&... arguments)
{
  Wrapper<First, 0>::operator()(std::forward<Args>(arguments)...);
}

template <class First>
template <class Arg>
  requires HasSetArgument<Wrapper<First, 0>, Arg>
void ObjectConstructor<First>::SetArgument(Arg&& arg)
{
  Wrapper<First, 0>::SetArgument(std::forward<Arg>(arg));
}

template <class First>
template <class Arg>
  requires(!HasSetArgument<Wrapper<First, 0>, Arg>)
void ObjectConstructor<First>::SetArgument(Arg&& arg)
{
  Expect(false, "No argument was updated!");
}
