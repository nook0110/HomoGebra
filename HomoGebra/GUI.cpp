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

void GUI::ImGuiWindow::Begin() const { ImGui::Begin(name.data()); }

void GUI::ImGuiWindow::End() const { ImGui::End(); }

void GUI::ObjectMenu::Construct() {}