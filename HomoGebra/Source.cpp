#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "GuiHandler.h"
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
  factory.OnPlane(PointEquation{HomogeneousCoordinate{100, 100}});

  auto menu = std::make_unique<Gui::ObjectMenu>(plane);

  Gui::Window gui_window("Hello", std::move(menu));

  Gui::GuiHandler handler(window);
  handler.AddConstructable(
      std::make_unique<Gui::Window>(std::move(gui_window)));

  while (window.isOpen())
  {
    sf::Event event{};

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();

      Gui::Global::ProcessEvent(event);

      if (auto const& io = ImGui::GetIO();
          io.WantCaptureMouse || io.WantCaptureKeyboard)
      {
        break;
      }

      plane.Update(event);
    }

    window.clear(sf::Color::White);

    Gui::Global::Update(window);

    plane.Update(window);

    window.draw(plane);

    handler.Construct();

    Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}