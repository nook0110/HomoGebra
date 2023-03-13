#include "GUI.h"

using namespace GUI;

sf::Clock Global::deltaClock;

void Global::Update(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Update method
  ImGui::SFML::Update(window, deltaClock.restart());
}

void Global::Render(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Render method
  ImGui::SFML::Render(window);
}

void Global::ProcessEvent(sf::Event event)
{
  // Just calls ImGui ImGui::SFML::ProcessEvent method
  ImGui::SFML::ProcessEvent(event);
}

void ImGuiWindow::Begin() const { ImGui::Begin(name.data()); }

void ImGuiWindow::End() const { ImGui::End(); }

void ObjectMenu::Construct() {}

ObjectMenu::HomogeneousCoordinateEditor::HomogeneousCoordinateEditor(
    const HomogeneousCoordinate& coordinate)
    : x_variable(coordinate.x),
      y_variable(coordinate.y),
      z_variable(coordinate.z)
{}

void ObjectMenu::HomogeneousCoordinateEditor::Construct()
{
  // Construct ComplexEditors

  // Construct description to identify the variable
  ImGui::Text("Variable x");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("x");
  x_variable.Construct();
  ImGui::PopID();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("y");
  y_variable.Construct();
  ImGui::PopID();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("z");
  z_variable.Construct();
  ImGui::PopID();
}

HomogeneousCoordinate ObjectMenu::HomogeneousCoordinateEditor::GetCoordinate()
    const
{
  return HomogeneousCoordinate{x_variable.GetNumber(), y_variable.GetNumber(),
                               z_variable.GetNumber()};
}

GUI::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::ComplexEditor(
    const complex& number)
    : real_part_(number.real()), imaginary_part_(number.imag())
{}

void GUI::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::Construct()
{
  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_);

  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_);
}

complex GUI::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::GetNumber()
    const
{
  return complex{real_part_, imaginary_part_};
}