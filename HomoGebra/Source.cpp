#include <SFML/OpenGL.hpp>

#include "ButtonsImplementations.h"
#include "EventConverter.h"
#include "GeometricObject.h"
#include "GeometricObjectFactory.h"
#include "Gui.h"
#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace HomoGebra::Editor
{
/**
 * \brief Class that represents a submenu that allows to edit a complex
 * number
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 */
class ComplexEditor final
{
 public:
  /**
   * \brief Construct menu with given number.
   *
   * \param number Number to edit.
   */
  explicit ComplexEditor(const Complex& number = Complex{});

  /**
   * \brief Renders the menu.
   *
   */
  void Construct();

  /**
   * \brief Renders the menu.
   *
   */
  void Construct() const;

  /**
   * \brief Returns the current number that was edited.
   *
   * \return Current number.
   */
  [[nodiscard]] Complex GetNumber() const;

 private:
  double real_part_;       //!< Real part of the number.
  double imaginary_part_;  //!< Imaginary part of the number.
};

void ComplexEditor::Construct()
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_);

  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_);

  // Pop id from ImGui stack
  ImGui::PopID();
}

void ComplexEditor::Construct() const
{
  // Push id to ImGui stack
  ImGui::PushID(this);

  auto real_part_copy = real_part_;
  // Construct input for real part of number
  ImGui::InputDouble("Real part", &real_part_copy, 0, 0, "%.6f",
                     ImGuiInputTextFlags_ReadOnly);

  auto imaginary_part_copy = imaginary_part_;
  // Construct input for imaginary part of number
  ImGui::InputDouble("Imaginary part", &imaginary_part_copy, 0, 0, "%.6f",
                     ImGuiInputTextFlags_ReadOnly);

  // Pop id from ImGui stack
  ImGui::PopID();
}

Complex ComplexEditor::GetNumber() const
{
  return Complex{real_part_, imaginary_part_};
}


}  // namespace HomoGebra::Editor

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
  equation.squares = {{HomoGebra::Complex{1.0f}, HomoGebra::Complex{0.f, 0.f},
                       HomoGebra::Complex{0.f, 0.f}}};
  equation.pair_products = {HomoGebra::Complex{-1.f}, HomoGebra::Complex{0},
                            HomoGebra::Complex{0.f, 0.f}};
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

      if (event.type == sf::Event::MouseWheelScrolled)
      {
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

    ImGui::Begin("Mouse position");
    ImGui::Text("Mouse position: (%f, %f)", mouse_position.x, mouse_position.y);
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