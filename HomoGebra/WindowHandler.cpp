#include "WindowHandler.h"

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

void Window::Construct()
{
  Begin();

  widget_->Construct();

  End();
}

Widget* Window::GetWidget() const { return widget_.get(); }

void Window::Begin() const { ImGui::Begin(name_.data()); }

void Window::End() const { ImGui::End(); }

void WindowHandler::Construct()
{
  for (const auto& renderable : constructable_objects_)
  {
    renderable->Construct();
  }
}

void Gui::WindowHandler::AddWindow(std::unique_ptr<Window> window)
{
  constructable_objects_.push_back(std::move(window));
}

void WindowHandler::DeleteWindow(Window* window)
{
  constructable_objects_.remove_if([window](std::unique_ptr<Window> const& ptr)
                                   { return ptr.get() == window; });
}

WindowHandler::WindowHandler(sf::RenderWindow& window) : window_(window) {}