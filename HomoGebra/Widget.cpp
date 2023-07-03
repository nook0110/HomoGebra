#include "Widget.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include <SFML/Graphics/Color.hpp>

#include "Assert.h"

using namespace Gui;

void ObjectMenu::Draw()
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  ImGui::ListBox("Type of objects", &current_type_, kTypesOfObjects.data(),
                 static_cast<int>(kTypesOfObjects.size()));

  // Construct selector of objects by their names
  ConstructObjectSelector();

  // Pop id
  ImGui::PopID();
}

void ObjectMenu::Construct(GeometricObject* object)
{
  // Go through all types of objects
  if (const auto point = dynamic_cast<Point*>(object))
  {
    Construct(point);
  }
  else if (const auto line = dynamic_cast<Line*>(object))
  {
    Construct(line);
  }
  else if (const auto conic = dynamic_cast<Conic*>(object))
  {
    Construct(conic);
  }
  else
  {
    Assert(false, "Bad pointer!");
  }
}

void ObjectMenu::Construct(Point* point)
{
  // Set current point
  point_submenu_.SetPoint(point);

  // Construct submenu
  point_submenu_.Draw();
}

void ObjectMenu::Construct(Line* line)
{
  // Construct line submenu
  // LineSubmenu submenu(line);

  // Construct submenu
  // submenu.Construct();
}

void ObjectMenu::Construct(Conic* conic) {}

std::vector<GeometricObject*> ObjectMenu::GetObjectsOfType(
    const ObjectType type) const
{
  // Go through all types of objects
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
      Assert(false, "ObjectType is incorrect");
      return {};
  }
}

void ObjectMenu::ConstructObjectSelector()
{
  // Go through all types of objects
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
void ObjectMenu::ConstructObjectSelector()
{
  // Get objects of type
  auto objects = plane_.GetObjects<GeometricObjectType>();

  static int current_object = 0;

  // Construct object selector
  ImGui::ListBox("Objects", &current_object, ObjectsNameGetter, &objects,
                 static_cast<int>(objects.size()));

  // Construct object editor
  if (current_object >= 0 && current_object < static_cast<int>(objects.size()))
  {
    Construct(dynamic_cast<GeometricObjectType*>(objects[current_object]));
  }
}

template <class GeometricObjectType>
GeometricObjectType*
Constructor::ObjectSelector<GeometricObjectType>::GetObject() const
{
  // Return object
  return object_;
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::SetObject(
    GeometricObjectType* object)
{
  // Set object
  object_ = object;
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::Draw()
{
  // Draw which object is selected
  DrawName();

  // Draw list of objects
  DrawList();

  // Draw setter of object
  DrawSetter();
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::Update(
    const UserEvent::Clicked& event)
{
  // Update object getter
  object_getter_.Update(event);
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::DrawName()
{
  if (!object_)
  {
    // If there is no object selected, draw nullptr
    ImGui::Text("nullptr");
    return;
  }

  // Draw name of object
  ImGui::Text(object_->GetName().c_str());
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::DrawList()
{
  // Get objects of type
  std::vector<GeometricObject*> objects =
      plane_.GetObjects<GeometricObjectType>();

  // Construct object selector
  if (ImGui::ListBox("Objects", &current_object_, ObjectsNameGetter, &objects,
                     static_cast<int>(objects.size())) &&
      (current_object_ >= 0 &&
       current_object_ < static_cast<int>(objects.size())))
  {
    // Select object
    object_ = dynamic_cast<GeometricObjectType*>(objects[current_object_]);
  }
}

template <class GeometricObjectType>
void Constructor::ObjectSelector<GeometricObjectType>::DrawSetter()
{
  std::string last_used_object_text = "Last used object: ";

  // Get last used object
  const auto object = object_getter_.GetLastObject();

  // Add name of object to text if it is not nullptr, otherwise add nullptr
  if (object)
  {
    last_used_object_text += object->GetName();
  }
  else
  {
    last_used_object_text += "nullptr";
  }

  // Draw last used object
  ImGui::Text(last_used_object_text.c_str());

  // Create button to select object
  if (ImGui::Button("Select object"))
  {
    SetObject(object);
  }
}

template class Gui::Constructor::ObjectSelector<Point>;

template void ObjectMenu::ConstructObjectSelector<GeometricObject>();
template void ObjectMenu::ConstructObjectSelector<Point>();
template void ObjectMenu::ConstructObjectSelector<Line>();
template void ObjectMenu::ConstructObjectSelector<Conic>();

using namespace Editor;

HomogeneousCoordinateEditor::HomogeneousCoordinateEditor(
    const HomogeneousCoordinate& coordinate)
    : x_variable_editor_(coordinate.x),
      y_variable_editor_(coordinate.y),
      z_variable_editor_(coordinate.z)
{}

void HomogeneousCoordinateEditor::Draw()
{
  // Construct ComplexEditors

  // Construct description to identify the variable
  ImGui::Text("Variable x");
  x_variable_editor_.Draw();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  y_variable_editor_.Draw();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  z_variable_editor_.Draw();
}

void HomogeneousCoordinateEditor::Draw() const
{
  // Construct ComplexEditors

  // Construct description to identify the variable
  ImGui::Text("Variable x");
  x_variable_editor_.Draw();

  // Construct description to identify the variable
  ImGui::Text("Variable y");
  y_variable_editor_.Draw();

  // Construct description to identify the variable
  ImGui::Text("Variable z");
  z_variable_editor_.Draw();
}

HomogeneousCoordinate HomogeneousCoordinateEditor::GetCoordinate() const
{
  return HomogeneousCoordinate{x_variable_editor_.GetNumber(),
                               y_variable_editor_.GetNumber(),
                               z_variable_editor_.GetNumber()};
}

ComplexEditor::ComplexEditor(const Complex& number)
    : real_part_(static_cast<double>(number.real())),
      imaginary_part_(static_cast<double>(number.imag()))
{}

void ComplexEditor::Draw()
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

void ComplexEditor::Draw() const
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

Complex ComplexEditor::GetNumber() const
{
  return Complex{real_part_, imaginary_part_};
}

PointSubmenu::PointSubmenu(Plane& plane, Point* point)
    : point_(point), plane_(plane)
{}

void PointSubmenu::SetPoint(Point* point) { point_ = point; }

void PointSubmenu::Draw()
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct name editor
  DrawNameEditor();

  // Construct current values
  DrawCurrentValues();

  // Construct values to edit
  DrawEditableValues();

  // Pop id from ImGui stack
  ImGui::PopID();
}

void PointSubmenu::DrawNameEditor()
{
  // Construct name editor
  ImGui::InputText("Name", &name_);

  // Construct name suggestions
  DrawNameSuggestions();

  // ImGui button that sets name
  if (ImGui::Button("Set name"))
  {
    // Set point name
    point_->SetName(name_);
  }
}

void PointSubmenu::DrawNameSuggestions()
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

void PointSubmenu::DrawEditableValues()
{
  ImGui::TextColored(sf::Color::Cyan, "New point coordinates");

  // Construct point coordinate editor
  coordinate_editor_.Draw();

  // ImGui button that sets coordinate
  if (ImGui::Button("Set coordinates"))
  {
    // Set point coordinate
    point_->SetEquation(PointEquation(coordinate_editor_.GetCoordinate()));
  }
}

void PointSubmenu::DrawCurrentValues() const
{
  ImGui::TextColored(sf::Color::Red, "Current point coordinates:");

  // Construct point current coordinates
  const auto current =
      HomogeneousCoordinateEditor(point_->GetEquation().GetEquation());

  current.Draw();
}