#include "ButtonsImplementations.h"
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
  equation.squares = {1, 1, -10000};
  equation.pair_products = {0, 0, 10};
  HomoGebra::ConicOnPlaneFactory{plane.get()}(equation);

  HomoGebra::LineByTwoPointButton line_by_two_point_button{plane.get()};
  HomoGebra::DeleteButton delete_button{plane.get()};

  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();

      HomoGebra::Gui::Global::ProcessEvent(event);

      if (auto const& io = ImGui::GetIO();
          io.WantCaptureMouse || io.WantCaptureKeyboard)
      {
        break;
      }

      plane->Update(event);
    }
    window.clear(sf::Color::White);

    HomoGebra::Gui::Global::Update(window);

    plane->Update(window);

    window.draw(*plane);

    line_by_two_point_button.Draw();
    delete_button.Draw();

    HomoGebra::Gui::Global::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}