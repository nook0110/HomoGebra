#include "GUI.h"

using namespace GUI;

sf::Clock Global::deltaClock;

void Global::Update(sf::RenderWindow& window)
{
	ImGui::SFML::Update(window, deltaClock.restart());
}

void  Global::Render(sf::RenderWindow& window)
{
	ImGui::SFML::Render(window);
}

void Global::ProcessEvent(sf::Event event)
{
	ImGui::SFML::ProcessEvent(event);
}