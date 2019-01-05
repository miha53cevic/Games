#pragma once
#include <SFML/Graphics.hpp>

class World
{
public:
	World(sf::Vector2u screen);
	~World() = default;

	void Update();
	void Draw(sf::RenderWindow *window);

	sf::FloatRect getEarthRect();

private:
	sf::Sprite m_earth;
	sf::Texture m_earthTex;

	sf::Sprite m_background;
	sf::Texture m_backgroundTex;
};

