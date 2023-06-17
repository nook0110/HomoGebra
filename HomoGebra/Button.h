#pragma once
#include <utility>

template <class Element, size_t index>
class Wrapper
{
 public:
  Wrapper() = default;

  template <class T,
            std::enable_if_t<
                !std::is_same_v<Wrapper,
                                std::remove_cv_t<std::remove_reference_t<T>>>,
                int> = 0>
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

  template <class Head, class... Tail,
            std::enable_if_t<
                !std::is_same_v<
                    Button, std::remove_cv_t<std::remove_reference_t<Head>>>,
                int> = 0>
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
template <class T,
          std::enable_if_t<
              !std::is_same_v<Wrapper<Element, index>,
                              std ::remove_cv_t<std::remove_reference_t<T>>>,
              int>>
Wrapper<Element, index>::Wrapper(T&& arg) : element_(std::forward<T>(arg))
{}

template <class Element, size_t index>
template <class... Args>
auto Wrapper<Element, index>::operator()(Args&&... args)
{
  return element_(args...);
}

template <class First, class... Rest>
template <class Head, class... Tail,
          std::enable_if_t<
              !std::is_same_v<Button<First, Rest...>,
                              std::remove_cv_t<std::remove_reference_t<Head>>>,
              int>>
Button<First, Rest...>::Button(Head&& head, Tail&&... tail)
    : Wrapper<First, sizeof...(Rest)>(std::forward<Head>(head)),
      Button<Rest...>(std::forward<Tail>(tail)...)
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