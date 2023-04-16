#include "GUI.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_stdlib.h>

#include <cassert>
#include <functional>
#include <utility>

using namespace Gui;
using namespace Editor;

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

void Gui::ObjectMenu::Construct(std::shared_ptr<Point> point)
{
  // Set current point
  point_submenu_.SetPoint(std::move(point));

  // Construct submenu
  point_submenu_.Construct();
}

void ObjectMenu::Construct(std::shared_ptr<Line> line)
{
  // Construct line submenu
  // LineSubmenu submenu(line);

  // Construct submenu
  // submenu.Construct();
}

void ObjectMenu::Construct(std::shared_ptr<Conic> conic) {}

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
      return {};
  }
}

bool ObjectMenu::ObjectsNameGetter(void* data, int index, const char** name)
{
  // Convert data to std::vector<std::shared_ptr<GeometricObject>> pointer
  const std::vector<std::shared_ptr<GeometricObject>>& objects =
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
                 static_cast<int>(objects.size()));

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

HomogeneousCoordinateEditor::HomogeneousCoordinateEditor(
    const HomogeneousCoordinate& coordinate)
    : x_variable_editor_(coordinate.x),
      y_variable_editor_(coordinate.y),
      z_variable_editor_(coordinate.z)
{}

void HomogeneousCoordinateEditor::Construct()
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

void HomogeneousCoordinateEditor::Construct() const
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

HomogeneousCoordinate HomogeneousCoordinateEditor::GetCoordinate() const
{
  return HomogeneousCoordinate{x_variable_editor_.GetNumber(),
                               y_variable_editor_.GetNumber(),
                               z_variable_editor_.GetNumber()};
}

HomogeneousCoordinateEditor::ComplexEditor::ComplexEditor(const Complex& number)
    : real_part_(static_cast<double>(number.real())),
      imaginary_part_(static_cast<double>(number.imag()))
{}

void HomogeneousCoordinateEditor::ComplexEditor::Construct()
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

void HomogeneousCoordinateEditor::ComplexEditor::Construct() const
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

Complex HomogeneousCoordinateEditor::ComplexEditor::GetNumber() const
{
  return Complex{real_part_, imaginary_part_};
}

PointSubmenu::PointSubmenu(Plane& plane, std::shared_ptr<Point> point)
    : point_(std::move(point)), plane_(plane)
{}

void PointSubmenu::SetPoint(std::shared_ptr<Point> point)
{
  point_ = std::move(point);
}

void PointSubmenu::Construct()
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct name editor
  ConstructNameEditor();

  // Construct current values
  ConstructCurrentValues();

  // Construct values to edit
  ConstructEditableValues();

  // Pop id from ImGui stack
  ImGui::PopID();
}

void PointSubmenu::ConstructNameEditor()
{
  // Construct name editor
  ImGui::InputText("Name", &name_);

  // Construct name suggestions
  ConstructNameSuggestions();

  // ImGui button that sets name
  if (ImGui::Button("Set name"))
  {
    // Set point name
    point_->SetName(name_);
  }
}

void PointSubmenu::ConstructNameSuggestions()
{
  // Check if user inputs text
  if (ImGui::IsItemActive())
  {
    const auto& name_generator = plane_.GetNameGenerator();

    // Add suggestions constructed on user input
    std::vector<std::string> suggestions;
    suggestions.push_back(
        static_cast<std::string>(name_generator.GenerateName(name_)));

    // Add suggestions constructed on point name
    suggestions.push_back(static_cast<std::string>(
        name_generator.GenerateName(point_->GetName())));

    // Add suggestion from generator
    suggestions.push_back(
        static_cast<std::string>(name_generator.GenerateName()));

    // Make suggestions unique
    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()),
                      suggestions.end());

    // Set suggestions positions
    ImGui::SetNextWindowPos(
        ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));

    ImGui::BeginTooltip();

    for (const auto& suggestion : suggestions)
    {
      // "Print" suggestion
      ImGui::TextUnformatted(suggestion.data());
    }

    ImGui::EndTooltip();
  }
}

void PointSubmenu::ConstructEditableValues()
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

void PointSubmenu::ConstructCurrentValues() const
{
  ImGui::TextColored(sf::Color::Red, "Current point coordinates:");

  // Construct point current coordinates
  const auto current =
      HomogeneousCoordinateEditor(point_->GetEquation().GetEquation());

  current.Construct();
}