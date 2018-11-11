#pragma once
#include "Snake.h"

class World
{
public:
	World(const int l_blockSize, sf::Vector2u l_windowSize);
	~World();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow* window);

private:
	sf::CircleShape m_apple;

	int m_BlockSize;
	sf::Vector2u m_windowSize;

	void RespawnApple();
};

