#include "FactoryWrapper.h"
#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "ObjectConstructionImplementations.h"
#include "ObjectConstructor.h"
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

  PointFactory point_factory(plane);
  auto first =
      point_factory.OnPlane(PointEquation{HomogeneousCoordinate{100, 100}});
  auto second =
      point_factory.OnPlane(PointEquation{HomogeneousCoordinate{300, 300}});

  ConicFactory conic_factory(plane);

  ConicEquation equation;
  equation.squares = {1, 1, -10000};
  equation.pair_products = {0, 0, 10};
  conic_factory.OnPlane(equation);

  auto line_by_two_points =
      std::make_unique<LineByTwoPoints>(plane, plane, plane);

  Gui::WindowHandler window_handler;

  auto selector =
      std::make_unique<Gui::Constructor::ObjectSelector<Point>>(plane);

  auto editor = std::make_unique<Gui::ObjectMenu>(plane);

  auto selector_window =
      std::make_unique<Gui::Window>("Hello", std::move(selector));
  auto editor_window = std::make_unique<Gui::Window>("Test", std::move(editor));

  window_handler.AddWindow(std::move(selector_window));
  window_handler.AddWindow(std::move(editor_window));

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

    window_handler.Construct();

    window.draw(plane);

    Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}