#include "ButtonBody.h"

#include <imgui.h>

namespace HomoGebra
{
bool ButtonBody::Draw() { return ImGui::Button("Apply"); }
}  // namespace HomoGebra