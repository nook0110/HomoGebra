#include "GUI.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_stdlib.h>

#include <cassert>
#include <functional>
#include <iostream>

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

  // Construct selector of objects by their names
  ConstructObjectSelector();

  // Pop id
  ImGui::PopID();

  // End constructing
  End();
}

void ObjectMenu::Construct(const std::shared_ptr<GeometricObject>& object)
{
  // Go through all types of objects
  if (std::dynamic_pointer_cast<Point>(object))
  {
    Construct(std::dynamic_pointer_cast<Point>(object));
  }
  else if (std::dynamic_pointer_cast<Line>(object))
  {
    Construct(std::dynamic_pointer_cast<Line>(object));
  }
  else if (std::dynamic_pointer_cast<Conic>(object))
  {
    Construct(std::dynamic_pointer_cast<Conic>(object));
  }
  else
  {
    assert(false);
  }
}

void Gui::ObjectMenu::Construct(const std::shared_ptr<Point>& object)
{
  // Set current point
  point_submenu_.SetPoint(object);

  // Construct submenu
  point_submenu_.Construct();
}

void ObjectMenu::Construct(const std::shared_ptr<Line>& line)
{
  // Construct line submenu
  // LineSubmenu submenu(line);

  // Construct submenu
  // submenu.Construct();
}

void ObjectMenu::Construct(const std::shared_ptr<Conic>& conic) {}

std::vector<std::shared_ptr<GeometricObject>> Gui::ObjectMenu::GetObjectsOfType(
    const ObjectType type) const
{
  switch (type)
  {
    case ObjectType::kAll:
      return plane_.GetObjects<GeometricObject>();
    case ObjectType::kPoint:
      return plane_.GetObjects<Point>();
    case ObjectType::kLine:
      return plane_.GetObjects<Line>();
    case ObjectType::kConic:
      return plane_.GetObjects<Conic>();
    default:
      assert(false);
  }
}

bool ObjectMenu::ObjectsNameGetter(void* data, int index, const char** name)
{
  // Convert data to std::vector<std::shared_ptr<GeometricObject>> pointer
  const std::vector<std::shared_ptr<GeometricObject>> objects =
      *static_cast<std::vector<std::shared_ptr<GeometricObject>>*>(data);

  // Check if index is valid
  if (index < 0 || index >= static_cast<int>(objects.size()))
  {
    return false;
  }

  // Set name
  *name = objects[index]->GetName().data();

  return true;
}

void ObjectMenu::ConstructObjectSelector()
{
  switch (static_cast<ObjectType>(current_type_))
  {
    case ObjectType::kAll:
      ConstructObjectSelector<GeometricObject>();
      break;
    case ObjectType::kPoint:
      ConstructObjectSelector<Point>();
      break;
    case ObjectType::kLine:
      ConstructObjectSelector<Line>();
      break;
    case ObjectType::kConic:
      ConstructObjectSelector<Conic>();
      break;
  }
}

template <typename GeometricObjectType>
void Gui::ObjectMenu::ConstructObjectSelector()
{
  // Get objects of type
  std::vector<std::shared_ptr<GeometricObject>> objects =
      plane_.GetObjects<GeometricObjectType>();

  // Construct object selector
  ImGui::ListBox("Objects", &current_object_, ObjectsNameGetter, &objects,
                 objects.size());

  // Construct object editor
  if (current_object_ >= 0 && current_object_ < objects.size())
  {
    Construct(std::dynamic_pointer_cast<GeometricObjectType>(
        objects[current_object_]));
  }
}

template void Gui::ObjectMenu::ConstructObjectSelector<GeometricObject>();
template void Gui::ObjectMenu::ConstructObjectSelector<Point>();
template void Gui::ObjectMenu::ConstructObjectSelector<Line>();
template void Gui::ObjectMenu::ConstructObjectSelector<Conic>();

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

  auto real_part_copy = real_part_;
  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_copy, 0, 0, "%.6f",
                     ImGuiInputTextFlags_ReadOnly);

  auto imaginary_part_copy = imaginary_part_;
  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_copy, 0, 0, "%.6f",
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
    : point_(point)
{}

void ObjectMenu::PointSubmenu::SetPoint(const std::shared_ptr<Point>& point)
{
  point_ = point;
}

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
  if (ImGui::Button("Set coordinates"))
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