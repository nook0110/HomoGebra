#pragma once

#include "SFML/Graphics.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

namespace GUI
{
  /**
 * \brief Global functions needed for Dear ImGui to work.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date February 2023
 *
 * \details Wraps Dear ImGui global methods and a clock for rendering.
 *
 * \see <a href="https://github.com/ocornut/imgui">Dear ImGui</a>
 * \see <a href="https://github.com/eliasdaler/imgui-sfml">ImGui-SFML v2.5</a>
*/
  class Global
  {
  public:
    /**
     * \brief Updates all Dear ImGui windows in sf::RenderWindow instance.
     *
     * \param window sf::RenderWindow where to update Dear ImGui windows.
     */
    static void Update(sf::RenderWindow& window);
    /**
     * \brief Renders all Dear ImGui windows in sf::RenderWindow instance.
     *
     * \param window sf::RenderWindow where to render Dear ImGui windows.
     */
    static void Render(sf::RenderWindow& window);
    /**
     * \brief Process event happened to update Dear ImGui windows.
     *
     * \param event Event that happened.
     */
    static void ProcessEvent(sf::Event event);
  private:
    /**
     * Static member data.
     */
    static sf::Clock deltaClock; //!< Clock that counts time for updates.
  };
}