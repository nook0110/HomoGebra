#include "Gui.h"

#include <imgui-SFML.h>
#include <imgui.h>

sf::Clock Gui::Global::delta_clock_;

void Gui::Global::Update(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Update method
  ImGui::SFML::Update(window, delta_clock_.restart());
}

void Gui::Global::Render(sf::RenderWindow& window)
{
  // Just calls ImGui ImGui::SFML::Render method
  ImGui::SFML::Render(window);
}

void Gui::Global::ProcessEvent(const sf::Event& event)
{
  // Just calls ImGui ImGui::SFML::ProcessEvent method
  ImGui::SFML::ProcessEvent(event);
}