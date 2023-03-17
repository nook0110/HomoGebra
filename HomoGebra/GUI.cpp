#include "GUI.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_stdlib.h>

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

void EditorWindow::Begin() const { ImGui::Begin(name_.data()); }

void EditorWindow::End() const { ImGui::End(); }

void ObjectMenu::Construct()
{
  // Begin constructing
  Begin();

  // Push id to ImGui stack
  ImGui::PushID(this);

  ImGui::ListBox("Type of objects", &current_type_, kTypesOfObjects.data(),
                 kTypesOfObjects.size());

  const auto objects = GetObjectsOfType(static_cast<ObjectType>(current_type_));

  Construct(objects);

  // Pop id from ImGui stack
  ImGui::PopID();

  // End constructing
  End();
}

void Gui::ObjectMenu::Construct(const std::shared_ptr<Point>& object)
{
  // Construct point submenu
  PointSubmenu submenu(object);

  // Construct submenu
  submenu.Construct();
}

void ObjectMenu::Construct(const std::shared_ptr<Line>& line)
{
  // Construct line submenu
  // LineSubmenu submenu(line);

  // Construct submenu
  // submenu.Construct();
}

void ObjectMenu::Construct(const std::shared_ptr<Conic>& conic) {}

void Gui::ObjectMenu::Construct(
    const std::vector<std::shared_ptr<GeometricObject>>& objects)
{
  for (auto& object : objects)
  {
    // Check type of object with dynamic_cast
    if (std::shared_ptr<Point> point = std::dynamic_pointer_cast<Point>(object))
    {
      Construct(point);
    }
    if (std::shared_ptr<Line> line = std::dynamic_pointer_cast<Line>(object))
    {
      Construct(line);
    }
    if (std::shared_ptr<Conic> conic = std::dynamic_pointer_cast<Conic>(object))
    {
      Construct(conic);
    }
  }
}

std::vector<std::shared_ptr<GeometricObject>> Gui::ObjectMenu::GetObjectsOfType(
    const ObjectType type) const
{
  switch (type)
  {
    case ObjectType::kAll:
      return plane_.GetObjects();
    case ObjectType::kPoint:
      return plane_.GetPoints();
    case ObjectType::kLine:
      return plane_.GetLines();
    case ObjectType::kConic:
      return plane_.GetConics();
  }
  throw std::invalid_argument("Invalid type of object");
}

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
  x_variable_editor_.Construct();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  y_variable_editor_.Construct();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  z_variable_editor_.Construct();
}

void ObjectMenu::HomogeneousCoordinateEditor::Construct() const
{
  // Construct ComplexEditors

  // Construct description to identify the variable
  ImGui::Text("Variable x");
  x_variable_editor_.Construct();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  y_variable_editor_.Construct();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  z_variable_editor_.Construct();
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
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_);

  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_);

  // Pop id from ImGui stack
  ImGui::PopID();
}

void Gui::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::Construct()
    const
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_, 0, 0, "%.6f",
                     ImGuiInputTextFlags_ReadOnly);

  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_, 0, 0, "%.6f",
                     ImGuiInputTextFlags_ReadOnly);

  // Pop id from ImGui stack
  ImGui::PopID();
}

Complex Gui::ObjectMenu::HomogeneousCoordinateEditor::ComplexEditor::GetNumber()
    const
{
  return Complex{real_part_, imaginary_part_};
}

ObjectMenu::PointSubmenu::PointSubmenu(const std::shared_ptr<Point>& point)
    : coordinate_editor_(point->GetEquation().GetEquation()), point_(point)
{}

void ObjectMenu::PointSubmenu::Construct()
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct current values
  ConstructCurrentValues();

  // Construct values to edit
  ConstructEditableValues();

  // Pop id from ImGui stack
  ImGui::PopID();
}

void ObjectMenu::PointSubmenu::ConstructEditableValues()
{
  ImGui::TextColored(sf::Color::Cyan, "New point coordinates");

  // Construct point coordinate editor
  coordinate_editor_.Construct();

  // ImGui button that sets coordinate
  if (ImGui::Button("Set coordinate:"))
  {
    // Set point coordinate
    point_->SetEquation(PointEquation(coordinate_editor_.GetCoordinate()));
  }
}

void ObjectMenu::PointSubmenu::ConstructCurrentValues() const
{
  ImGui::TextColored(sf::Color::Red, "Current point coordinates:");

  // Construct point current coordinates
  const auto current =
      HomogeneousCoordinateEditor(point_->GetEquation().GetEquation());

  current.Construct();
}