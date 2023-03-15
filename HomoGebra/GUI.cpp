#include "GUI.h"

#include <imgui-SFML.h>
#include <imgui.h>

using namespace Gui;

sf::Clock Global::delta_clock_;

void Global::Update(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Update method
  ImGui::SFML::Update(window, delta_clock_.restart());
}

void Global::Render(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Render method
  ImGui::SFML::Render(window);
}

void Global::ProcessEvent(const sf::Event& event)
{
  // Just calls ImGui ImGui::SFML::ProcessEvent method
  ImGui::SFML::ProcessEvent(event);
}

void ImGuiWindow::Begin() const { ImGui::Begin(name.data()); }

void ImGuiWindow::End() const { ImGui::End(); }

void ObjectMenu::Construct() {}

ObjectMenu::HomogeneousCoordinateEditor::HomogeneousCoordinateEditor(
    const HomogeneousCoordinate& coordinate)
    : x_variable_editor_(coordinate.x),
      y_variable_editor_(coordinate.y),
      z_variable_editor_(coordinate.z)
{}

void ObjectMenu::HomogeneousCoordinateEditor::Construct()
{
  // Construct ComplexEditors

  // Construct description to identify the variable
  ImGui::Text("Variable x");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("x");
  x_variable_editor_.Construct();
  ImGui::PopID();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("y");
  y_variable_editor_.Construct();
  ImGui::PopID();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  // Pushing id to ImGui stack so that it can be used to identify the variable
  ImGui::PushID("z");
  z_variable_editor_.Construct();
  ImGui::PopID();
}

HomogeneousCoordinate ObjectMenu::HomogeneousCoordinateEditor::GetCoordinate()
    const
{
  return HomogeneousCoordinate{x_variable_editor_.GetNumber(),
                               y_variable_editor_.GetNumber(),
                               z_variable_editor_.GetNumber()};
}

Gui::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::ComplexEditor(
    const Complex& number)
    : real_part_(static_cast<double>(number.real())),
      imaginary_part_(static_cast<double>(number.imag()))
{}

void Gui::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::Construct()
{
  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_);

  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_);
}

Complex Gui::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::GetNumber()
    const
{
  return Complex{real_part_, imaginary_part_};
}