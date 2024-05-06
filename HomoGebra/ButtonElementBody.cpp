#include "ButtonElementBody.h"

#include <imgui.h>

#include <vector>

#include "GuiUtilities.h"

namespace HomoGebra
{
template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::Draw()
{
  ImGui::PushID(this);

  // Draw which object is selected
  DrawName();

  // Draw list of objects
  DrawList();

  // Draw setter of object
  DrawSetter();

  ImGui::PopID();
}

template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::SetObject(
    GeometricObjectType* object)
{
  object_ = object;
  current_object_ = -1;
}

template <class GeometricObjectType>
GeometricObjectType* ObjectSelectorBody<GeometricObjectType>::GetObject() const
{
  return object_;
}

template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::Update(
    const PlaneEvent::ObjectRemoved& object_removed)
{
  if (GetObject() == object_removed.removed_object)
  {
    SetObject(nullptr);
  }
}

template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::DrawName()
{
  if (!GetObject())
  {
    // If there is no object selected, draw nullptr
    ImGui::Text("nullptr");
    return;
  }

  // Draw name of object
  ImGui::Text(GetObject()->GetName().c_str());
}

template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::DrawList()
{
  // Get objects of type
  std::vector<GeometricObject*> objects =
      plane_->GetObjects<GeometricObjectType>();

  // Construct object selector
  if (ImGui::ListBox("Objects", &current_object_, ObjectsNameGetter, &objects,
                     static_cast<int>(objects.size())) &&
      (current_object_ >= 0 &&
       current_object_ < static_cast<int>(objects.size())))
  {
    // Select object
    SetObject(dynamic_cast<GeometricObjectType*>(objects[current_object_]));
  }
}

template <class GeometricObjectType>
void ObjectSelectorBody<GeometricObjectType>::DrawSetter()
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

template class ObjectSelectorBody<GeometricObject>;
template class ObjectSelectorBody<Point>;
template class ObjectSelectorBody<Line>;
template class ObjectSelectorBody<Conic>;
}  // namespace HomoGebra