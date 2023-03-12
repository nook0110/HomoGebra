#include "GUI.h"
#include "GeometricObject.h"
#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
int main()
{
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 16;
  settings.majorVersion = 3;
  settings.minorVersion = 0;
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Window Title",
                          sf::Style::Default, settings);
  ImGui::SFML::Init(window);

  window.setFramerateLimit(60);
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      GUI::Global::ProcessEvent(event);
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color::White);

    GUI::Global::Update(window);

    ImGui::Begin("Test window");
    ImGui::Text("Hello world!");
    ImGui::End();

    GUI::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}