#include "ButtonsImplementations.h"
#include "EventConverter.h"
#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "Gui.h"
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
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "HomoGebra",
                          sf::Style::Titlebar | sf::Style::Close, settings);

  window.setView(sf::View({0, 0}, {1000, 1000}));

  if (!ImGui::SFML::Init(window))
  {
    return 1;
  }

  window.setFramerateLimit(60);
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  auto plane = std::make_unique<HomoGebra::Plane>();

  auto first = HomoGebra::PointOnPlaneFactory{plane.get()}(
      HomoGebra::PointEquation{HomoGebra::HomogeneousCoordinate{100, 100}});
  auto second = HomoGebra::PointOnPlaneFactory{plane.get()}(
      HomoGebra::PointEquation{HomoGebra::HomogeneousCoordinate{300, 300}});

  HomoGebra::ConicEquation equation;
  equation.squares = {-100, 40, -1000000};
  equation.pair_products = {10, -100, 142};
  auto conic = HomoGebra::ConicOnPlaneFactory{plane.get()}(equation);

  HomoGebra::LineByTwoPointButton line_by_two_point_button{plane.get()};
  HomoGebra::DeleteButton delete_button{plane.get()};

  HomoGebra::EventConverter converter(&window);
  converter.Attach(plane.get());
  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      HomoGebra::Gui::Global::ProcessEvent(event);

      if (auto const& io = ImGui::GetIO();
          io.WantCaptureMouse || io.WantCaptureKeyboard)
      {
        break;
      }

      converter.Update(event);
    }
    window.clear(sf::Color::White);

    HomoGebra::Gui::Global::Update(window);

    // print distance from mouse to all objects
    auto mouse_position =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));
    ImGui::Begin("Distance");
    for (auto const& object : plane->GetObjects<HomoGebra::GeometricObject>())
    {
      ImGui::Text("%s: %f", object->GetName().c_str(),
                  object->GetDistance(mouse_position));
    }
    ImGui::End();

    plane->UpdateBodies(window);  // TODO: Should be called only when window
                                  // size changes or it moves
    window.draw(*plane);

    line_by_two_point_button.Draw();
    delete_button.Draw();

    HomoGebra::Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}