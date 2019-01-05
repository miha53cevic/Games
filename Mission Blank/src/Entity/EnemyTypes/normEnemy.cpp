#include "normEnemy.h"

normEnemy::normEnemy(float x, float y, sf::Vector2u screen)
	: Enemy(x, y, screen)
{
	// Load Sprite
	if (!m_enemyTex.loadFromFile("tex/normEnemy.png"))
	{
		// Error
	}
	else
	{
		m_enemy.setTexture(m_enemyTex);
	}
}

