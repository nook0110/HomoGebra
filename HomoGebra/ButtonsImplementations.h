#pragma once
#include "Button.h"
#include "ButtonElement.h"
#include "GeometricObjectFactory.h"
#include "imgui.h"

template <class ButtonClass>
class WindowButton : public ButtonClass
{
 public:
  explicit WindowButton(std::string name, Plane* plane)
      : ButtonClass(plane), name_(std::move(name))
  {}

  void Draw()
  {
    ImGui::Begin(name_.data());
    ButtonClass::Draw();
    ImGui::End();
  }

 private:
  std::string name_;
};

class LineByTwoPointButton
    : public WindowButton<Button<ObjectSelector<Point>, ObjectSelector<Point>,
                                 FactoryWrapper<LineByTwoPointsFactory>>>
{
 public:
  explicit LineByTwoPointButton(Plane* plane)
      : WindowButton("Line by two points", plane)
  {}
};

class DeleteButton
    : public WindowButton<Button<ObjectSelector<GeometricObject>, Deleter>>
{
 public:
  explicit DeleteButton(Plane* plane) : WindowButton("Delete button", plane) {}
};