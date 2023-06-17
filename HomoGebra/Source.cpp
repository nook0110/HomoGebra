#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "SFML/Graphics.hpp"
#include "WindowHandler.h"
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
                          sf::Style::Titlebar, settings);

  if (!ImGui::SFML::Init(window))
  {
    return 1;
  }

  window.setFramerateLimit(60);
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  Plane plane;

  Gui::WindowHandler gui_handler;

  auto selector =
      std::make_unique<Gui::Constructor::ObjectSelector<Point>>(plane, window);

  auto editor = std::make_unique<Gui::ObjectMenu>(plane);

  auto selector_window =
      std::make_unique<Gui::Window>("Hello", std::move(selector));
  auto editor_window = std::make_unique<Gui::Window>("Test", std::move(editor));

  gui_handler.AddWindow(std::move(selector_window));
  gui_handler.AddWindow(std::move(editor_window));

  PointFactory point_factory(plane);
  auto first =
      point_factory.OnPlane(PointEquation{HomogeneousCoordinate{100, 100}});
  auto second =
      point_factory.OnPlane(PointEquation{HomogeneousCoordinate{300, 300}});

  ConicFactory conic_factory(plane);

  ConicEquation equation;
  equation.squares = {1, 1, -10000};
  equation.pair_products = {0, 1, 1};
  conic_factory.OnPlane(equation);

  LineFactory line_factory(plane);

  line_factory.ByTwoPoints(first, second);

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

    gui_handler.Construct();

    Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}