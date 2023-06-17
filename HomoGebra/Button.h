#pragma once

template <class Element, size_t index>
class Wrapper
{
 public:
  Wrapper() = default;

  template <class T>
  Wrapper(T&& arg);

  template <class... Args>
  auto operator()(Args&&... args);

 private:
  Element element_;
};

template <class First, class... Rest>
class Button : public Wrapper<First, sizeof...(Rest)>, public Button<Rest...>
{
 public:
  Button() = default;

  template <class Head, class... Tail>
  Button(Head&& head, Tail&&... tail);

  template <class... Arguments>
  void ConstructObject(Arguments&&... arguments);
};

template <class First>
class Button<First> : public Wrapper<First, 0>
{
 public:
  Button();

  template <class... Arguments>
  void ConstructObject(Arguments&&... arguments);
};

template <class Element, size_t index>
template <class T>
Wrapper<Element, index>::Wrapper(T&& arg) : element_(arg)
{}

template <class Element, size_t index>
template <class... Args>
auto Wrapper<Element, index>::operator()(Args&&... args)
{
  return element_(args...);
}

template <class First, class... Rest>
template <class Head, class... Tail>
Button<First, Rest...>::Button(Head&& head, Tail&&... tail)
    : Wrapper<First, sizeof...(Rest)>(head), Button<Rest...>(tail...)
{}

template <class First, class... Rest>
template <class... Arguments>
void Button<First, Rest...>::ConstructObject(Arguments&&... arguments)
{
  Button<Rest...>::ConstructObject(
      arguments..., Wrapper<First, sizeof...(Rest)>::operator()());
}

template <class First>
Button<First>::Button() : Wrapper<First, 0>()
{}

template <class First>
template <class... Arguments>
void Button<First>::ConstructObject(Arguments&&... arguments)
{
  Wrapper<First, 0>::operator()(arguments...);
}