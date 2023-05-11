#include "GuiHandler.h"

#include <imgui-SFML.h>
#include <imgui.h>

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

void GuiHandler::Construct()
{
  for (const auto& renderable : constructable_objects_)
  {
    renderable->Construct();
  }
}

void Gui::GuiHandler::AddConstructable(
    std::unique_ptr<Constructable> constructable)
{
  constructable_objects_.push_back(std::move(constructable));
}

void GuiHandler::DeleteConstructable(Constructable* constructable)
{
  constructable_objects_.remove_if(
      [constructable](std::unique_ptr<Constructable> const& ptr)
      { return ptr.get() == constructable; });
}

GuiHandler::GuiHandler(sf::RenderWindow& window) : window_(window) {}

void Window::Construct()
{
  Begin();

  widget_->Construct();

  End();
}

void Window::Begin() const { ImGui::Begin(name_.data()); }

void Window::End() const { ImGui::End(); }