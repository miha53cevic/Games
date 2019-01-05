#include "World.h"

World::World(sf::Vector2u screen)
{
	// Load Earth Sprite
	if (!m_earthTex.loadFromFile("tex/earth.png"))
	{
		// Error
	}
	else
	{
		m_earth.setTexture(m_earthTex);
		m_earth.setOrigin(m_earthTex.getSize().x / 2, m_earthTex.getSize().y / 2);
		m_earth.setPosition(screen.x / 2, screen.y / 2);
	}

	// Load Background
	if (!m_backgroundTex.loadFromFile("tex/background.jpg"))
	{
		// Error
	}
	else
	{
		m_background.setTexture(m_backgroundTex);
		m_background.setPosition(sf::Vector2f(0, 0));
	}
}

void World::Update()
{

}

void World::Draw(sf::RenderWindow *window)
{
	window->draw(m_background);
	window->draw(m_earth);
}

sf::FloatRect World::getEarthRect()
{
	sf::FloatRect earth = m_earth.getGlobalBounds();
	return earth;
}

