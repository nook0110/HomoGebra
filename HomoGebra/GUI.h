#pragma once

#include "SFML/Graphics.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

namespace GUI
{
	class Global
	{
		static sf::Clock deltaClock;
	public:
		static void Update(sf::RenderWindow& window);
		static void Render(sf::RenderWindow& window);
		static void ProcessEvent(sf::Event event);
	};
}