#include "World.h"

World::World(const int l_blockSize, sf::Vector2u l_windowSize) : m_apple(l_blockSize / 2)
{
	m_apple.setPosition(rand() % ((int)l_windowSize.x / l_blockSize) * l_blockSize, rand() % ((int)l_windowSize.y / l_blockSize) * l_blockSize);
	m_apple.setFillColor(sf::Color::Red);

	m_windowSize = l_windowSize;
	m_BlockSize = l_blockSize;
}
World::~World() {}

void World::Update(Snake& l_player)
{

	//Check if food is eaten
	if (l_player.getSnakeHeadXY() == (sf::Vector2i)m_apple.getPosition())
	{
		l_player.growSnake();
		RespawnApple();
	}
}

void World::Render(sf::RenderWindow* window)
{
	window->draw(m_apple);
}

void World::RespawnApple()
{
	m_apple.setPosition(rand() % ((int)m_windowSize.x / m_BlockSize) * m_BlockSize, rand() % ((int)m_windowSize.y / m_BlockSize) * m_BlockSize);
}



