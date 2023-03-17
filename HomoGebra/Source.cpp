#include "GUI.h"
#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
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
  if (!ImGui::SFML::Init(window))
  {
    return 1;
  }

  window.setFramerateLimit(60);
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  Plane plane;
  PointFactory factory(plane);
  factory.OnPlane(PointEquation{});

  Gui::ObjectMenu menu(plane, std::string("Plane"));

  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      Gui::Global::ProcessEvent(event);
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color::White);

    Gui::Global::Update(window);

    menu.Construct();

    Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}